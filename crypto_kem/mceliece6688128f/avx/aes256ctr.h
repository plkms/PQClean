#ifndef PQCLEAN_MCELIECE6688128F_AVX_aes256ctr_H
#define PQCLEAN_MCELIECE6688128F_AVX_aes256ctr_H

#include <stddef.h>
#include <stdint.h>

#include "aes.h"


void PQCLEAN_MCELIECE6688128F_AVX_aes256ctr(
    uint8_t *out,
    size_t outlen,
    const uint8_t nonce[AESCTR_NONCEBYTES],
    const uint8_t key[AES256_KEYBYTES]
);

#endif
