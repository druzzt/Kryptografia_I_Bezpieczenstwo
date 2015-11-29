//
//  keygen.c
//  
//
//  Created by Arkadiusz Lewandowski on 29.11.2015.
//  gcc myrsa.c keygen.c -o PROGRAM -lgmp -lpthread
//  ./PROGRAM [g] [2] [powers of 2] [PRIMES/b$x$$$]

#include "myrsa.h"
#define MAXMPZ 8 // no more threads which will be effective on my lap

int conv_to_int(char x){
    x=abs(x);
    if(x<48) return (int)(48+abs((x%10)));
    if(x>57) return (int)(57-abs((x%10)));
    return (int)((x));
}

void create_RSA_pair(mpz_t n,
                    mpz_t e,
                    mpz_t d,
                    mpz_t *primes, int xPrimes,
                    mpz_t u){
}

int RSA_keys(int k, int l, char *argv){
    printf("\tthreads: %d\n\tn-bit: %d\n",k,l);
    mpz_t p,q;
    mpz_t x;
    mpz_init(x);
    mpz_t n;
    mpz_init(n);
    mpz_init(p);
    mpz_init(q);
    mpz_t gcd;
    mpz_init(gcd);
    mpz_t e;
    mpz_init(e);
    mpz_t d;
    mpz_init(d);
    char *poq_str;
    //poq_str=calloc(,sizeof(char));
    char *fbited_chararr;
    char *xbited_chararr;
    unsigned long long int e_int = 65537; // may become much biger its ULLI
    int err,i,j=0;
    FILE *f;
    f=fopen(argv,"r");
    if(!f){ printf("cannot open that file"); return -1; }
    

    xbited_chararr=calloc( l, sizeof(char) );
    fread(xbited_chararr,l,1,f);  /* read from /dev/random */
    fclose(f);
    xbited_chararr[l]='\0';       /* assing null terminating symbol */
    for(i=0;i<l/4;i++){           /* convert all the strange ascii symbols into int*/
        if(i==(l/4)/k) printf("\n");
        xbited_chararr[i]=conv_to_int(xbited_chararr[i]);
        printf("%c",xbited_chararr[i]);
    } printf("\n");
    

    mpz_set_ui(n,1);
    mpz_set_ui(x,1);
    //mpz_init(poq_str);
    mpz_t poq[MAXMPZ];
    for(i=0;i<k;i++){
        mpz_init(poq[i]);
    }
    mpz_t mympz_minus_1[MAXMPZ];
    for (int i=0; i<k; i++)
    {
        mpz_init(mympz_minus_1[i]);
    }
    

    fbited_chararr=calloc(((l/4)/k)+1,sizeof(char));
    int saver=0;
    int tmp=0;
    j=0;
   
    for(i=0;i<(l/4);i++){ /* first part of array ( getting poq[j] ) */
        fbited_chararr[tmp]=xbited_chararr[i];
        //printf("%c",fbited_chararr[tmp]);
        tmp++;
        if(tmp==(l/4)/k){
            fbited_chararr[((l/4)/k)+1]='\0';
            mpz_set_str(poq[j],fbited_chararr,10);
            gmp_printf("--#-->%Zd\n",poq[j]);
            //gmp_printf("------->%Zd\n",poq[j]);
            mpz_sub_ui(mympz_minus_1[j],poq[j],1);
            mpz_mul(n,n,poq[j]);
            mpz_mul(x,x,mympz_minus_1[j]);
            j++;
            tmp=0;;
            printf("\n");
        }
    } //printf("\n",fbited_chararr);
        
        
    
    
    
    /* now i've got two primes from TASK #2. - NO! MORE PRIMES! actualy k primes */
    /*
     *  Calculate n (=pq) ie the 1024 bit modulus
     *  and x (=(p-1)(q-1)).
     */
   /* mpz_t p_minus_1,q_minus_1;
    mpz_init(p_minus_1);
    mpz_init(q_minus_1);
    
    mpz_sub_ui(p_minus_1,p,(unsigned long int)1);
    mpz_sub_ui(q_minus_1,q,(unsigned long int)1);
    
    mpz_mul(x,p_minus_1,q_minus_1);
    
    / * Calculate n... * /
    mpz_mul(n,p,q);*/
    //gmp_printf("\t n: ---> %Zd\n",n);

    /*
     *  Get small odd integer e such that gcd(e,x) = 1.
     */
    
    
    
    while(mpz_cmp_ui(gcd,(unsigned long int)1)!=0)
    {
        mpz_gcd_ui(gcd,x,e_int);
        /* try the next odd integer... */
        e_int += 2;
    }
    
    mpz_set_ui(e,e_int);
    
    /*
     *  Calculate unique d such that ed = 1(mod x)
     */
    
    if(mpz_invert(d,e,x)==0)
    {
        printf("\nOOPS : Could not find multiplicative inverse!\n");
        printf("\nTrying again...");
        RSA_keys(k,l,argv);
    }
    
    gmp_printf("\n\tPublicKey: (e=%Zd,\n\t\tn=%Zd)\n\tPrivateKey:(d=%Zd)\n",e,n,d);
    
    /* now just save it to a file */
    char *n_str;
    n_str=calloc(l*l+1,sizeof(char));
    mpz_get_str(n_str,10,n);
    f=fopen("RSAKEYS/PublicRSAkey","w");
    fprintf(f,"%s\n%llu",n_str,e_int);
    fclose(f);
    
    char *d_str;
    d_str=calloc(l*l+1,sizeof(char));
    mpz_get_str(d_str,10,d);
    f=fopen("RSAKEYS/PrivateRSAkey","w");
    fprintf(f,"%s\n%llu\n%s\n",n_str,e_int,d_str);
    
    for(i=0;i<k;i++){
        gmp_printf("->%Zd\n",poq[i]);
        mpz_get_str(d_str,10,poq[i]);
        printf("=====>%s\n",d_str);
        fprintf(f,"%s\n",d_str);
    }
//    fprintf(f,"",NULL);
    fclose(f);
    
    /* DONE */
    mpz_clear(e);
    mpz_clear(d);
    mpz_clear(x);
    for(i=0;i<k;i++){
        mpz_clear(poq[i]);
        mpz_clear(mympz_minus_1[i]);
    }
    mpz_clear(gcd);
    mpz_clear(n);
    

    return 0;
}
