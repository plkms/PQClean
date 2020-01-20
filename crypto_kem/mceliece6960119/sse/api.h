#ifndef PQCLEAN_MCELIECE6960119_SSE_API_H
#define PQCLEAN_MCELIECE6960119_SSE_API_H

#define PQCLEAN_MCELIECE6960119_SSE_CRYPTO_ALGNAME "Classic McEliece 6960119"
#define PQCLEAN_MCELIECE6960119_SSE_CRYPTO_PUBLICKEYBYTES 1047319
#define PQCLEAN_MCELIECE6960119_SSE_CRYPTO_SECRETKEYBYTES 13908
#define PQCLEAN_MCELIECE6960119_SSE_CRYPTO_CIPHERTEXTBYTES 226
#define PQCLEAN_MCELIECE6960119_SSE_CRYPTO_BYTES 32


int PQCLEAN_MCELIECE6960119_SSE_crypto_kem_enc(
    unsigned char *c,
    unsigned char *key,
    const unsigned char *pk
);

int PQCLEAN_MCELIECE6960119_SSE_crypto_kem_dec(
    unsigned char *key,
    const unsigned char *c,
    const unsigned char *sk
);

int PQCLEAN_MCELIECE6960119_SSE_crypto_kem_keypair
(
    unsigned char *pk,
    unsigned char *sk
);

#endif

