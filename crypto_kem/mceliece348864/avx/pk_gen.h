#ifndef PK_GEN_H
#define PK_GEN_H
/*
  This file is for public-key generation
*/


#include "gf.h"

int PQCLEAN_MCELIECE348864_AVX_pk_gen(unsigned char * /*pk*/, uint32_t * /*perm*/, const unsigned char * /*sk*/);

#endif

