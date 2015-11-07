/* @author druzzter */
#include <ao/ao.h>
#include <stdio.h>
#include <stdlib.h>
#include <mpg123.h>
#include <pthread.h>
#include  <sys/types.h>
//#include "player.h"

/*----------------------------------------------------------------------------------------------------------*/
#include <unistd.h>
char *getpass(const char *prompt);
/*----------------------------------------------------------------------------------------------------------*/
#define BASH "read -s PAS; echo $PAS > password.txt;"
#define BASH2 "rm password.txt;"
#define BASH3 "rm PLAYME.NOW"
//#define BASH3 "./sit aes ctr KEYSTORE/keystore scsv outputDEC d"
#define BITS 8
#define NUM_THREADS 1 //safest option to have only one thread at once for music playing...
/*----------------------------------------------------------------------------------------------------------*/
int rc;
long t;
int err;
size_t done;
void *status;
mpg123_handle *mh;
size_t ubuffer_size;
pthread_attr_t attr;
unsigned char *ubuffer;
pthread_t threads[NUM_THREADS];
unsigned char *K1 = {'z','a','s','z','y','t','e','h','2','4','5','2','y','7','3','h'};
/*----------------------------------------------------------------------------------------------------------*/
int driver;
ao_device *dev;
/*----------------------------------------------------------------------------------------------------------*/
ao_sample_format format;
int channels, encoding;
long rate;
/*----------------------------------------------------------------------------------------------------------*/
void decodeFile(char *filer)
{
    decrypt(filer);
}
/*----------------------------------------------------------------------------------------------------------*/
void *AO_PLAYER(void *threadid)
{
    FILE *fp;
    fp=fopen("password.txt","r");
    if(!fp) fprintf(stderr, "Password not available");
    char temp[512];
    while(fgets(temp, 512, fp) != NULL)
        printf("%s",temp);

    long tid;
    tid = (long)threadid;
   
    //now play it.
    printf("Playing from thread %ld\n", tid);
    system(BASH2);
    while (mpg123_read(mh, ubuffer, ubuffer_size, &done) == MPG123_OK)
        ao_play(dev, ubuffer, done);
    system (BASH3);
    pthread_exit(NULL);
}
/*----------------------------------------------------------------------------------------------------------*/
int main(int argc, char *argv[])
{
    if(argc < 2)
        exit(0);

    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    system(BASH);
    //do something with interactive password
    //now decrypt file
    decodeFile(argv[1]);
    /* initializations */
    ao_initialize();
    driver = ao_default_driver_id();
    mpg123_init();
    mh = mpg123_new(NULL, &err);
    ubuffer_size = mpg123_outblock(mh);
    ubuffer = (unsigned char*) malloc(ubuffer_size * sizeof(unsigned char));

    /* open the file and get the decoding format */
    mpg123_open(mh, "PLAYME.NOW");
    mpg123_getformat(mh, &rate, &channels, &encoding);

    /* set the output format and open the output device */
    format.bits = mpg123_encsize(encoding) * BITS;
    format.rate = rate;
    format.channels = channels;
    format.byte_format = AO_FMT_NATIVE;
    format.matrix = 0;
    dev = ao_open_live(driver, &format, NULL);

    /* decode and play */
    for(t=0; t<NUM_THREADS; t++)
    {
        rc = pthread_create(&threads[t], &attr, AO_PLAYER, (void *)t);
        if (rc)
        {
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }

    /* clean up */
    pthread_attr_destroy(&attr);
    for(t=0; t<NUM_THREADS; t++)
    {
        rc = pthread_join(threads[t], &status);
        if (rc)
        {
            printf("ERROR; return code from pthread_join() is %d\n", rc);
            exit(-1);
        }
        printf("Main: completed join with thread %ld having a status of %ld\n",t,(long)status);
    }
    
    printf("Main: program completed. Exiting.\n");
    
    free(ubuffer);
    ao_close(dev);
    mpg123_close(mh);
    mpg123_delete(mh);
    mpg123_exit();
    ao_shutdown();

    return 0;
}
/*----------------------------------------------------------------------------------------------------------*/