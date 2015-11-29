/* @Author Arkadiusz Lewandowski
 * @PROGRAM DO GENEROWANIA n-BITOWYCH LICZB PIERWSZYCH
 * gcc cryptrand.c fermat.c miller-rabin.c -o PROGRAM -lgmp - lpthread
 * time ./PROGRAM [thread quantity] [# of bits for prime number]
 */
/* Header containing all required to get this program working */
#include "cryptlib.h"

/* tricky converter for pure randomnes of /dev/random into integer */
int conv_to_int(char x){
    x=abs(x);
    if(x<48) return (int)(48+abs((x%10)));
    if(x>57) return (int)(57-abs((x%10)));
    return (int)((x));
}

/* every threads task to find prime number */
void *LICZ()
{
    
    /* Every thread initializes his own prime number exploration  */
    unsigned long long int randval1;
    ulli R_N_4_Me[precision];           /* Array containing unsigned long long ints for rand purpose  */
    int probed=0;                       /* counter for thread's probing to achieve prime number  */
    int bitsizeofprime2;
    int pierwsza=0;
    char *xbited_chararr;
    int err,i;
    FILE *f;                            /* Using /dev/random file  */
    //pthread_mutex_lock(&lock);
    f = fopen( "/dev/random", "r" );
    //pthread_mutex_unlock(&lock);
    if( !(f) ) return 0;                /* program couldn't open /dev/random  */
    
    if(bitsizeofprime%8==0  ||
       bitsizeofprime%16==0 ||
       (bitsizeofprime%8==0 &&          /* check if there is proper size request  */
       bitsizeofprime%16==0 &&          /* for reading prime number  */
       bitsizeofprime%32==0 )
       ){
        bitsizeofprime2=bitsizeofprime/8;
        xbited_chararr=calloc( bitsizeofprime2, sizeof(char) );
    }else{
        printf("Given size of prime number is wrong! \t[powers of 2 only].\n");
        fclose(f);
        return 0;
    }
    
    /* Read for threads own purpose of using 'precision'sized array of random numbers  */
    /* and in miller's method */
    while( pierwsza<precision ){
        fread(&randval1, ( bitsizeofprime2 ), 1, f);
        R_N_4_Me[pierwsza++]=randval1;
    }
    
    /* check if number read from /dev/random is probable of being prime  */
    while(pierwsza){
        fread(xbited_chararr,bitsizeofprime2,1,f);  /* read from /dev/random */
        xbited_chararr[bitsizeofprime2]='\0';       /* assing null terminating symbol */
        for(i=0;i<bitsizeofprime2;i++){             /* convert all the strange ascii symbols into int */
            xbited_chararr[i]=conv_to_int(xbited_chararr[i]); }
                                                    /* now get rid of useless numbers */
        xbited_chararr[0]=xbited_chararr[0]|1;      /* so assign to the first bit a one */
        xbited_chararr[bitsizeofprime2-1]=xbited_chararr[bitsizeofprime2-1]|1; /* and to the last too */
        
        mpz_t n;
        mpz_init(n);
        err = mpz_set_str( n, xbited_chararr, 10 ); /* if err is 0 then something went wrong */
        if(err!=0){ printf("error\n"); return 0; }
      
        /* NOW CHECK FOR ITS PRIMARITY */
        //if(Fermat(n)){                                  /*  MUST REPAIR FERMAT.C  */
            if(Miller( n, precision )){
                //if(mpz_probab_prime_p(n,precision)){
                mpz_set_str_uip(n);
                gmp_printf("%Zd",n);
                pierwsza=0;
            }else
                probed++;
        // }else probed++;
        mpz_clear(n);
    }

    /* loop is ended only if thread has found very probable prime number  */
    fclose(f);
    return 0;
}

/* it's a main. */
int main(int argc, char* argv[])
{
    int ch=argc,i;
    pthread_t *t;
    
    if ( argc>1 )       ch  = atoi(argv[1]);
    if ( argc>2 )       bitsizeofprime   =  atoi(argv[2]);
    
    pthread_mutex_init(&lock, NULL);
    
    t = ( pthread_t * ) malloc( ch * sizeof( pthread_t ) );
    
    for( i=0; i<ch; i++ )
    { pthread_create( &t[i], NULL, LICZ, NULL ); }
    
    for( i=0; i<ch; i++ )
    { pthread_join( t[i], NULL ); }
     pthread_mutex_destroy(&lock);
    
    return 0;
}




