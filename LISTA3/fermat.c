//
//  fermat.c
//  
//
//  Created by Arkadiusz Lewandowski on 26.11.2015.
//
//

#include "cryptlib.h"
#include <time.h>
#define bits(x) ((sizeof(x))*8)
    ulli x=2, y=7, z=1;

#define MAXTRIES 10
//ll MAXNUM=18446744073709551615;
//ll MINNUM=18446744073700000000;


//ll b, e, m, result;
//mpz_t b, e, m, result;
//ll Fmodulo(ll b, ll e, ll m){
int Fmodulo(mpz_t b, mpz_t e, mpz_t m){
    //ll result=1;
    mpz_t dwa;
    //mpz_init2(dwa,bits(x));
    mpz_init(dwa);
    mpz_t r;
    //mpz_init2(r,bits(x));
      mpz_init(r);
    mpz_set_ui(dwa,2);
    mpz_t result;
    //mpz_init2(result,bits(x));
    mpz_init(result);
    //while(e>0){
    while(mpz_cmp_ui(e,(unsigned long int)2)){
        //if(e%2==1){
        mpz_mod_ui(r,e,2);
        if(mpz_cmp_si(r,0)){
            //result=(result*b)%m;
            mpz_mul(result,result,b);
            mpz_mod(result,result,m);
        }
        //b=(b*b)%m;
        mpz_mul(b,b,b);
        mpz_mod(b,b,m);
        //e=e/2;
        mpz_div_ui(e,e,2);
    }
    //return result%m;
    mpz_mod(result,result,m);
    //free_function(dwa,bits(x));
    //free_function(r,bits(x));
    //free_function(result,bits(x));
    
    return 0;
}


//int Fermat(ll n)
int Fermat(mpz_t n)
{    printf("ferm");

    //ll a;
    mpz_t a;
    //mpz_init2(a,bits(x));
    mpz_init(a);
    int i;

    for(i = 1; i <= 10; i++)
    {
        //a = rand() % (n - 1) + 1;
        mpz_t n1;
        //mpz_init2(n1,bits(x));
        mpz_init(n1);
        mpz_t t;
        //mpz_init2(t,bits(x));
        mpz_init(t);
        mpz_set_ui(t,1);
        mpz_sub(n1,n,t);
        mpz_t rander;
        //mpz_init2(rander,bits(x));
        mpz_init(rander);
        ll ran = rand();
        mpz_set_ui(rander,ran);
        mpz_mod(a,rander,(n1));
        //a+=1;
        mpz_add_ui(a,a,1);
        if(Fmodulo(a, n - 1, n) != 1)
        {
            //free_function(a,bits(x));
            //free_function(n1,bits(x));
            //free_function(t,bits(x));
            //free_function(rander,bits(x));
            
            return 0;
        }
    }
    //free_function(a,bits(x));
    //free_function(n1,bits(x));
    //free_function(t,bits(x));
    //free_function(rander,bits(x));
    return 1;
}


/*
  // new testing module with gmp
int main(){
    mpz_t TESTOWY;
    //mpz_init2(TESTOWY,bits(x));
    mpz_init(TESTOWY);
    mpz_t TESTOWY2;
    mpz_init(TESTOWY2);
    x=1;
    z=1;
    y=1;
    y=y<<52;
  
    
    mpz_set_ui(TESTOWY,y);
    mpz_set_ui(TESTOWY2,x);
    mpz_nextprime(TESTOWY2,TESTOWY);
//    mpz_mod(TESTOWY,TESTOWY2,TESTOWY);
    gmp_printf("%Zd\n",TESTOWY2);
    //printf("%d\n",Fermat(TESTOWY));
    //free_function(TESTOWY,bits(x));
    //free_function(TESTOWY2,bits(x));
    return 0;
}
 //*/




/* // testing module'old
 int main()
{
    ll prime = 0;
    ll flag = 0;
    ll tries;
    ll start;
    long curtime;
    ll p;
    
    curtime = time(NULL);
    srand((ll) curtime);
    printf("Checking range [%llu, %llu] for prime numbers.\n",MINNUM,MAXNUM);
    if(MINNUM % 2 == 0)
    {
        start = MINNUM + 1;
    }
    else
    {
        start = MINNUM;
    }
    
    printf("Trying Fermat test with seed %ld \n\n",curtime);
    prime = 0;
    
    for(tries = 1; tries <= MAXTRIES; tries++)
    {
        clock_t tic = clock();
        for(p = start; p <= MAXNUM; p += 2)
        {
            if(Fermat(p))
                prime++;
        }
        
        clock_t toc = clock();
        printf("Probabilistic algorithm: Found %llu primes in %f seconds.(tries = %llu)\n", prime, (double)(toc - tic) / CLOCKS_PER_SEC,tries);
        prime = 0;
    } 
    
    return 0;
}//*/