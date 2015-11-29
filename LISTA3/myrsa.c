/* @Author Arkadiusz Lewandowski
 * RSA generator, encryptor, decryptor
 * gcc myrsa.c -o PROGRAM -lgmp -lpthread
 * ./PROGRAM [g/e/d] [k] [d]
 */

#include "myrsa.h"


int main(int argc, char* argv[]){
    /* check if it has all parameters */
    if(argc<4){
        printf("%s requires more arguments.\n", argv[0]);
        return -1;
    }
    /* check which one mode is it */
    if(argv[1][0]=='g' || argv[1][0]=='G'){
        printf("generating:\n");
        
        /* check how much threads does he want */
        if(argv[2][0]>'8' || argv[2][0]<'1'){
            printf("cannot generate that amount of threads\n");
            return -3;
        }
        /* check how much bit long primes should be */
        if(argv[3][0]>'7' || argv[3][0]<'1'){
            printf("something wrong with d parameter:\n \
                   wrong bit number.\n");
            return -4;
        }
          /* now it is ready to start working */
        
         RSA_keys(atoi(argv[2]),atoi(argv[3]), argv[4]);
        
    }else if(argv[1][0]=='e' || argv[1][0]=='E'){
        printf("encrypting\n");
        if(argv[2][0]==' ') { printf("nothing to encrypt\n"); return -3; }
        FILE *fin, *fout;
        fin=fopen(argv[2],"r");
        if(argv[3][0]==' ') { printf("nowhere to save\n"); return -4; }
        if(argv[4][0]==' ') { printf("how much to pack together?\n"); return -5; }
        fout=fopen(argv[3],"w");
        RSA_traditional(fin,fout,atoi(argv[4]),atoi(argv[5]));
        fclose(fin);
        fclose(fout);
    }else if(argv[1][0]=='d' || argv[1][0]=='D'){
        printf("decrypting\n");
        if(argv[2][0]==' ') { printf("nothing to decrypt\n"); return -3; }
        FILE *fin, *fout;
        fin=fopen(argv[2],"r");
        if(argv[3][0]==' ') { printf("nowhere to save\n"); return -4; }
        if(argv[4][0]==' ') { printf("how much to pack together?\n"); return -5; }
        fout=fopen(argv[3],"w");
        RSA_traditional_decrypt(fin,fout,atoi(argv[4]),atoi(argv[5]));
        fclose(fin);
        fclose(fout);

    }else{
        printf("wrong action\n");
        return -2;
    }
    
  
    
   
    
    
    return 0;
}