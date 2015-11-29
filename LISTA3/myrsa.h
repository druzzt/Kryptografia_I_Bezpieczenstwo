//
//  myrsa.h
//  
//
//  Created by Arkadiusz Lewandowski on 28.11.2015.
//
//

#ifndef myrsa_h
#define myrsa_h

#include "cryptlib.h"


struct RSA_PUB {
    mpz_t n; // modulus
    mpz_t e; //exponent
};

struct RSA_PRIV {
    mpz_t n; //modulus
    mpz_t e; //public exponent
    mpz_t d; //private exponent
    mpz_t *p; //primes x
    mpz_t u; //inverse of pmodq
};

struct RSA_PUB *rsau;
struct RSA_PRIV *rsar;

int RSA_keys(int k, int d,char *argv);
int RSA_traditional(FILE *fin, FILE *fout, int bitsize, int packetedAs);
int RSA_traditional_decrypt(FILE *fin, FILE *fout, int bitsize, int packetedAs);
int RSA_enc();
int RSA_dec();


#endif /* myrsa_h */
