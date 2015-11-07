//
//  player.h
//  
//
//  Created by druzzter on 07.11.2015.
//
//
/*----------------------------------------------------------------------------------------------------------*/
#ifndef player_h
#define player_h
#include <openssl/aes.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define CLEARSCREEN     "clear;pwd;ls"
#define SHOWFILES       "echo \"\";"
#define READPASSWD      "read -s PAS; echo $PAS > password.txt; cat password.txt; "
#define REMOPASSWD      "rm password.txt"
#define SHPASSWD        "cat password.txt"
#define _cast_LL(X)         system(X)
#define _console_c(X)       system(X)
/*----------------------------------------------------------------------------------------------------------*/
#define uchar       unsigned char
#define uint        unsigned int
/*----------------------------------------------------------------------------------------------------------*/
struct ctr_state {
    uchar ivec[16];
    uint num;
    uchar ecount[16];
};
/*----------------------------------------------------------------------------------------------------------*/
FILE *fp;
FILE *rp;
FILE *op;
FILE *ks; // keystore pointer assigned in arguments of program being launched
size_t count;
char * buffer;
AES_KEY key;
char newtmp[512];
/*----------------------------------------------------------------------------------------------------------*/
int bytes_read, bytes_written;
uchar indata[AES_BLOCK_SIZE];
uchar outdata[AES_BLOCK_SIZE];
uchar ID[55];
uchar KEY[17];
uchar k2[] = "0987poiu";
uchar ckey[] =  "1234567890e54321"; // It is 128bits though..
uchar iv[8] = {1234};
uchar IDofKS[255];
int i;
struct ctr_state state;
/*----------------------------------------------------------------------------------------------------------*/
#endif /* player_h */

