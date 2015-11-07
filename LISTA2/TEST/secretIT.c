#include "player.h"
/*----------------------------------------------------------------------------------------------------------*/
int init_ctr(struct ctr_state *state, const unsigned char iv[8])
{
    state->num = 0; 
    memset(state->ecount, 0, 16);      
    memset(state->ivec + 8, 0, 8);  
    memcpy(state->ivec, iv, 8); 
}
/*----------------------------------------------------------------------------------------------------------*/
void readCKEY(char *argv, char *str)
{
    ks=fopen(argv,"r");
    size_t len = 0;
    ssize_t read;
    if(!ks)
    {
        fprintf(stderr, "Cannot open key store\n");
    }
    uchar ch;
    if(ks==NULL)
    {
        fputs("Keystore not found", stderr);
        exit(1);
    }
    int line_num = 1;
    int find_result = 0;
    char temp[512];
    while(fgets(temp, 512, ks) != NULL)
    {
        if((strstr(temp, str)) != NULL)
        {
            printf("\nA matching found on line: %d\n", line_num);
            printf("\n%s\n", temp);
            strcpy(newtmp,temp);
            find_result++;
        }
        line_num++;
    }
    char * pch;
    pch = strtok (newtmp," ,.-\t");
    int token=0;
    while (pch != NULL)
    {
        token++;
        if(token==2){ break;}
        pch = strtok (NULL, " ,.-\t");
    }
    printf("!#$> %s\t%d\n",pch,strlen(pch));
    if(find_result == 0)
    {
        printf("\nSorry, couldn't find a matching.\n");
    }
    fclose(ks);
}
/*----------------------------------------------------------------------------------------------------------*/

void encrypt(char *file_to)
{
  //Opening files where text plain text is read and ciphertext stored      
  fp=fopen(file_to,"rb");
  op=fopen("outputENC","w+b");
  if (fp==NULL) {fputs ("File error1",stderr); exit (1);}
  if (op==NULL) {fputs ("File error2",stderr); exit (1);}

  //Initializing the encryption KEY
  AES_set_encrypt_key(ckey, 128, &key); 

  //Encrypting Blocks of 16 bytes and writing the output with ciphertext
    while (1)
    {
    init_ctr(&state, iv);           //Counter call
    bytes_read = fread(indata, 1, AES_BLOCK_SIZE, fp); 
    AES_ctr128_encrypt(indata, outdata, bytes_read, &key, state.ivec, state.ecount, &state.num);    
    bytes_written = fwrite(outdata, 1, bytes_read, op); 
        if (bytes_read < AES_BLOCK_SIZE)
            break;
    }

  fclose (fp); 
  fclose (op);
  free (buffer); 
}
/*----------------------------------------------------------------------------------------------------------*/
void decrypt(char *file_from)
{
  //Opening files where text cipher text is read and the plaintext recovered         
  rp=fopen("outputDEC","w+b");
  op=fopen(file_from,"rb");
  if (rp==NULL) {fputs ("File error3",stderr); exit (1);}
  if (op==NULL) {fputs ("File error4",stderr); exit (1);}

  //Initializing the encryption KEY
  AES_set_encrypt_key(ckey, 128, &key); 

  //Encrypting Blocks of 16 bytes and writing the output.txt with ciphertext   
  while (1)
  {
    init_ctr(&state, iv);//Counter call
    bytes_read = fread(indata, 1, AES_BLOCK_SIZE, op);  
    AES_ctr128_encrypt(indata, outdata, bytes_read, &key, state.ivec, state.ecount, &state.num); 
    bytes_written = fwrite(outdata, 1, bytes_read, rp); 
     if (bytes_read < AES_BLOCK_SIZE)
     break;
    }   
  fclose (rp); 
  fclose (op);
  free (buffer); 
}
/*----------------------------------------------------------------------------------------------------------*/
int main(int argc, char *argv[])
{
    if(argc>1 && argv[1][0]=='a' && argv[1][1]=='e' && argv[1][2]=='s')
    {
        if(argc>2 && argv[2][0]=='c' && argv[2][1]=='t' && argv[2][2]=='r')
        {
            if(argc>3)
            {
                if(argc>4)
                {
                    //_console_c(CLEARSCREEN);
                    //readCKEY(argv[3],argv[4]);
                }
                if(argc>4)
                {
                    _cast_LL(READPASSWD);
                    
                    _cast_LL(SHPASSWD);
                    
                    _cast_LL(REMOPASSWD);
                    
                    if(argv[6][0]=='e')
                    {
                        printf("encrypting %s\n",argv[5]);
                        encrypt(argv[5]);
                    }
                    else
                    {
                        printf("decrypting %s\n",argv[5]);
                        decrypt(argv[5]);
                    }
                }
                
                fclose(ks);
                
            }
            else
            {
                fprintf(stderr, "Lack of path to the keystore\n");
            }
        }
        else
        {
            fprintf(stderr, "Not valid encryption mode\n");
        }
    }
    else
    {
            fprintf(stderr, "Not valid encryption\n");
    }
    
  return 0;
}
/*----------------------------------------------------------------------------------------------------------*/