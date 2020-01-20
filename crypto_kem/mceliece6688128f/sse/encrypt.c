/*
  This file is for Niederreiter encryption
*/

#include "encrypt.h"

#include "params.h"
#include "randombytes.h"
#include "util.h"

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "gf.h"

/* input: public key pk, error vector e */
/* output: syndrome s */
extern void PQCLEAN_MCELIECE6688128F_SSE_syndrome_asm(unsigned char *s, const unsigned char *pk, unsigned char *e);

/* output: e, an error vector of weight t */
static void gen_e(unsigned char *e) {
    size_t i, j;
    int eq, count;

    uint16_t ind[ SYS_T * 2 ];
    uint8_t *ind8 = (uint8_t *)ind;
    uint32_t ind32[ SYS_T * 2 ];
    uint64_t e_int[ (SYS_N + 63) / 64 ];
    uint64_t one = 1;
    uint64_t mask;
    uint64_t val[ SYS_T ];

    while (1) {
        randombytes(ind8, sizeof(ind));
        for (i = 0; i < sizeof(ind); i += 2) {
            ind[i / 2] = (uint16_t)ind8[i + 1] << 8 | ind8[i];
        }

        for (i = 0; i < SYS_T * 2; i++) {
            ind[i] &= GFMASK;
        }

        // moving and counting indices in the correct range

        count = 0;
        for (i = 0; i < SYS_T * 2; i++) {
            if (ind[i] < SYS_N) {
                ind32[ count++ ] = ind[i];
            }
        }

        if (count < SYS_T) {
            continue;
        }

        // check for repetition

        eq = 0;

        for (i = 1; i < SYS_T; i++) {
            for (j = 0; j < i; j++) {
                if (ind32[i] == ind32[j]) {
                    eq = 1;
                }
            }
        }

        if (eq == 0) {
            break;
        }
    }

    for (j = 0; j < SYS_T; j++) {
        val[j] = one << (ind32[j] & 63);
    }

    for (i = 0; i < (SYS_N + 63) / 64; i++) {
        e_int[i] = 0;

        for (j = 0; j < SYS_T; j++) {
            mask = i ^ (ind32[j] >> 6);
            mask -= 1;
            mask >>= 63;
            mask = -mask;

            e_int[i] |= val[j] & mask;
        }
    }

    for (i = 0; i < (SYS_N + 63) / 64 - 1; i++) {
        PQCLEAN_MCELIECE6688128F_SSE_store8(e, e_int[i]);
        e += 8;
    }

    for (j = 0; j < (SYS_N % 64); j += 8) {
        e[ j / 8 ] = (e_int[i] >> j) & 0xFF;
    }
}

/* input: public key pk */
/* output: error vector e, syndrome s */
void PQCLEAN_MCELIECE6688128F_SSE_encrypt(unsigned char *s, unsigned char *e, const unsigned char *pk) {
    gen_e(e);

    PQCLEAN_MCELIECE6688128F_SSE_syndrome_asm(s, pk, e);
}

