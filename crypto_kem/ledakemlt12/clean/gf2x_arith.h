#ifndef GF2X_ARITH_H
#define GF2X_ARITH_H

#include "gf2x_limbs.h"

/*
 * Elements of GF(2)[x] are stored in compact dense binary form.
 *
 * Each bit in a byte is assumed to be the coefficient of a binary
 * polynomial f(x), in Big-Endian format (i.e., reading everything from
 * left to right, the most significant element is met first):
 *
 * byte:(0000 0000) == 0x00 ... f(x) == 0
 * byte:(0000 0001) == 0x01 ... f(x) == 1
 * byte:(0000 0010) == 0x02 ... f(x) == x
 * byte:(0000 0011) == 0x03 ... f(x) == x+1
 * ...                      ... ...
 * byte:(0000 1111) == 0x0F ... f(x) == x^{3}+x^{2}+x+1
 * ...                      ... ...
 * byte:(1111 1111) == 0xFF ... f(x) == x^{7}+x^{6}+x^{5}+x^{4}+x^{3}+x^{2}+x+1
 *
 *
 * A "machine word" (A_i) is considered as a DIGIT.
 * Bytes in a DIGIT are assumed in Big-Endian format:
 * E.g., if sizeof(DIGIT) == 4:
 * A_i: A_{i,3} A_{i,2} A_{i,1} A_{i,0}.
 * A_{i,3} denotes the most significant byte, A_{i,0} the least significant one.
 * f(x) ==   x^{31} + ... + x^{24} +
 *         + x^{23} + ... + x^{16} +
 *         + x^{15} + ... + x^{8}  +
 *         + x^{7}  + ... + x^{0}
 *
 *
 * Multi-precision elements (i.e., with multiple DIGITs) are stored in
 * Big-endian format:
 *           A = A_{n-1} A_{n-2} ... A_1 A_0
 *
 *           position[A_{n-1}] == 0
 *           position[A_{n-2}] == 1
 *           ...
 *           position[A_{1}]  ==  n-2
 *           position[A_{0}]  ==  n-1
 */


#define GF2X_MUL PQCLEAN_LEDAKEMLT12_CLEAN_gf2x_mul_comb
// #define GF2X_MUL gf2x_mul_comb

static inline void gf2x_add(DIGIT Res[], const DIGIT A[], const DIGIT B[], size_t nr) {
    for (size_t i = 0; i < nr; i++) {
        Res[i] = A[i] ^ B[i];
    }
}

/* PRE: MAX ALLOWED ROTATION AMOUNT : DIGIT_SIZE_b */
void PQCLEAN_LEDAKEMLT12_CLEAN_right_bit_shift_n(size_t length, DIGIT in[], unsigned int amount);

/* PRE: MAX ALLOWED ROTATION AMOUNT : DIGIT_SIZE_b */
void PQCLEAN_LEDAKEMLT12_CLEAN_left_bit_shift_n(size_t length, DIGIT in[], unsigned int amount);

void GF2X_MUL(int nr, DIGIT Res[], int na, const DIGIT A[], int nb, const DIGIT B[]);


#endif
