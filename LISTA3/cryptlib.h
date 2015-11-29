//
//  cryptlib.h
//  
//
//  Created by Arkadiusz Lewandowski on 25.11.2015.
//
//

#ifndef cryptlib_h
#define cryptlib_h

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <inttypes.h>
#include <gmp.h>
#define ll unsigned long long int
#define false 0
#define true 1
#define mpz_set_str_uip(x) (mpz_nextprime((x),(x)))
#define bool int
#include <gmp.h>
#include<pthread.h>
#include<unistd.h>
#define ulli unsigned long long int
static int d=0;
const static int precision = 50;
static int bitsizeofprime=0;
//bool Miller(mpz_t p,int iteration, ulli *R_N_4_Me);
//bool Miller(mpz_t p,int iteration, mpz_t *R_N_4_Me);
bool Miller(mpz_t p,int iteration);
int Fermat(mpz_t n);
pthread_mutex_t lock;
#endif /* cryptlib_h */
