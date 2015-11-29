//
//  encrypt.c
//  
//
//  Created by Arkadiusz Lewandowski on 29.11.2015.
//  encrypts whole file with RSA-bitsize
//  nothing to know about this one..
//  NEED REPAIR I THINK.
//  gcc myrsa.c keygen.c encrypt.c decrypt.c -o my -lgmp -lpthread
//  ./PROG e [tester] [newtester] [power of 2] [packeted]

#include "myrsa.h"
#include <string.h>

int encrypter(char *msg, FILE *fout, mpz_t e, mpz_t n){
    printf("brak stacku?");
    
    return 0;
}

int RSA_traditional(FILE *fin, FILE *fout, int bitsize, int packetedAs){
    
    //printf("\t\tbitsize-->%d\n\t\tpacketSize-->%d\n",bitsize,packetedAs);
    char *xbited_chararr;
    int err,i,j=0;
    xbited_chararr=calloc( bitsize, sizeof(char) );
    char e_str[65], n_str[2048];
    mpz_t e, n;
    mpz_init(e);
    mpz_init(n);
    FILE *PRK;
    PRK=fopen("RSAKEYS/PublicRSAkey","r"); // always in this folder.
    fscanf(PRK,"%s\n",n_str); // read the fucken e
    fscanf(PRK,"%s\n",e_str); // now the n
    fclose(PRK);
    mpz_set_str(e,e_str,10); // copy it into mpz_t pointers
    mpz_set_str(n,n_str,10);

    //gmp_printf("\t--> %Zd\n\t--> %Zd\n",e,n); // check if it works...
    if(packetedAs<1 || packetedAs>100)
    {
        /* safest numbers are in the range 1-100 for 1024 bit RSA */
        if(packetedAs<1)
        {
            printf("invalid input");
            return -1;
        }
        else
            printf("something went wrong with RSA_traditional:packetedAs");
    }
    
    
    char ch;            /* char for reading purpose */
    //char stread[1000];      /* chararray as string */
    char *stread;
    stread=calloc(1000,sizeof(char));
    //char numberized[3*1000+1];
    char *numberized;
    numberized = calloc(3*1000+1,sizeof(char));
    char *chara;//[4]; chara[0]='0'; chara[0]='1'; chara[2]='0'; chara[3]='0';
    chara=calloc(3*1000+1,sizeof(char));


    i=0;
    mpz_t M;
    mpz_init(M);
    mpz_t c;
    mpz_init(c);
    while( ( ch= fgetc(fin) ) != EOF ) /* very ?bad?, but i like it */
    {
        stread[i%(packetedAs)]=ch;
        if( i%(packetedAs)==0 && i>0 ){
            //stread[i%(packetedAs)]='\0';
            
            strcpy(numberized, "");
            
            for(j=0;j<packetedAs;j++){ // sum of datagram it won't ever be larger than slli
                
                sprintf(chara,"%03d",(int)stread[j]);

                //printf("%c\t%d\n",stread[j],stread[j]);
                
                strcat(numberized,chara);
                
                printf("))))->%s\n",numberized);
                
            }
            mpz_set_str(M,numberized,10);
            gmp_printf("-->%Zd\n",M);
            mpz_powm(c,M,e,n);
            mpz_get_str(stread,10,c);
            
            fprintf(fout,"%s\n",stread); /* save encrypted file */
           
        }
    i++;
    }
    
    free(chara);
    mpz_clear(M);
    mpz_clear(c);
    //system("cat newtester");
    return 0;
}