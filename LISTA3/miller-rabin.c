//
//  miller-rabin.c
//  
//
//  Created by Arkadiusz Lewandowski on 25.11.2015.
//
//
#include "cryptlib.h"

 //* calculates (a * b) % c taking into account that a * b might overflow
ll mulmod(ll a, ll b, ll mod)
{
    ll x = 0,y = a % mod;
    while (b > 0){
        if (b % 2 == 1)
            x = ((x%mod) + (y%mod)) % mod;
        y = ((y%mod) * 2) % mod;
        b /= 2;
    }
    return x % mod;
}

 //* modular exponentiation
ll modulo(ll base, ll exponent, ll mod)
{
    ll x = 1;
    ll y = base;
    while (exponent > 0){
        if (exponent % 2 == 1)
            x = ((x%mod) * (y%mod)) % mod;
        y = ((y%mod) * (y%mod)) % mod;
        exponent = exponent / 2;
    }
    return x % mod;
}


 //* Miller-Rabin primality test, iteration signifies the accuracy
 
bool Miller(mpz_t p,int iteration)
{
   // if (p < 2 || (p != 2 && p % 2==0)) return false;
    mpz_t modulo;
    mpz_init(modulo);
    mpz_mod_ui(modulo,p,2);
    if( mpz_cmp_si(p,2) && !mpz_cmp_si(modulo,0) ) return false;
    
    /*ll s = p - 1;
    while (s % 2 == 0) s/=2;
    int i=0;
   // printf("\t\tRN4M:%llu p:%llu, s:%llu\n",R_N_4_Me[i],p,s);
    // *for(i=0;i<precision;i++) printf("%llu, ", R_N_4_Me[i]);* /
    for (int i = 0; i < iteration; i++)
    {
        ll a = ((R_N_4_Me[i] % (p - 1)) + 1);ll temp = s;
       // printf("\t\tRN4M:%llu p:%llu, temp:%llu a:%llu\n",R_N_4_Me[i],p,temp,a);
        ll mod = modulo(a, temp, p);
        while (temp != p - 1 && mod != 1 && mod != p - 1)
        {
            mod = mulmod(mod, mod, p);
            temp *= 2;
        }
        if (mod != p - 1 && temp % 2 == 0) return false;
    }*/
    return true;
}
