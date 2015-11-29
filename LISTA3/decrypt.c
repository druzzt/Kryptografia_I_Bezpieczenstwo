//
//  decrypt.c
//  
//
//  Created by Arkadiusz Lewandowski on 29.11.2015.
//  just chilling and decrypting.
//   NEED REPAIR!!!

#include "myrsa.h"
#include <string.h>

int conv_to_string(char *str, FILE *fout){
    unsigned int i=0;
    int tmpnum;
    char strmod[1000];
    
    /* make the message length an integral multiple
     *  of 3 by adding zeroes to the left if required
     */
    if(strlen(str)%3 == 1)
    {
        strcpy(strmod,"00");
        strcat(strmod,str);
    }
    else if(strlen(str)%3 == 2)
    {
        strcpy(strmod,"0");
        strcat(strmod,str);
    }
    else
        strcpy(strmod,str);
    
    
    while(i<=strlen(strmod)-3)
    {
        tmpnum = strmod[i] - 48;
        tmpnum = 10*tmpnum + (strmod[i+1] - 48);
        tmpnum = 10*tmpnum + (strmod[i+2] - 48);
        i += 3;
        fprintf(fout,"%c",tmpnum);
    }
    return 0;
}


int RSA_traditional_decrypt(FILE *fin, FILE *fout, int bitsize, int packetedAs){
    
    char ciphertext[1000];    /* ciphertext */
    char decrypted[1000];     /* after deciphering */
    mpz_t M, c, d, n, e, poq[8];
    mpz_init(M);     mpz_init(c);     mpz_init(d);     mpz_init(n);
    FILE *fpub, *fpriv;
    //fpub=fopen("RSAKEYS/PublicRSAkey","r");
    //fscanf(fpub,"%s\n",ciphertext);
    //fclose(fpub);
    fpriv=fopen("RSAKEYS/PrivateRSAkey","r");
    fscanf(fpriv,"%s\n",ciphertext);
    mpz_set_str(n,ciphertext,10);
    fscanf(fpriv,"%s\n",ciphertext);
    mpz_set_str(e,ciphertext,10);
    fscanf(fpriv,"%s\n",ciphertext);
    mpz_set_str(d,ciphertext,10);
    fclose(fpriv);
    
    while(fscanf(fin,"%s\n",ciphertext)>0)
    {
        //printf("%s\n",ciphertext);
        mpz_set_str(c,ciphertext,10);
        //gmp_printf(" <--> %Zd\n",c);
        /* M=c^d(mod n) */
        mpz_powm(M,c,d,n);
        gmp_printf("%Zd\n",M);
        mpz_get_str(decrypted, 10, M);
        conv_to_string(decrypted, fout);
    }
    
    return 0;
}