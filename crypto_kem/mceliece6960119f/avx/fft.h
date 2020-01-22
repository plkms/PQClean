#ifndef FFT_H
#define FFT_H
/*
  This file is for the Gao-Mateer FFT
  sse http://www.math.clemson.edu/~sgao/papers/GM10.pdf
*/


#include "params.h"
#include "vec128.h"
#include "vec256.h"
#include <stdint.h>

void PQCLEAN_MCELIECE6960119F_AVX_fft(vec256  /*out*/[][GFBITS], vec128 * /*in*/);

#endif

