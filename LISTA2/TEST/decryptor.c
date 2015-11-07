#include "player.h"

int init_ctr(struct ctr_state *state, const unsigned char iv[8])
{
    state->num = 0;
    memset(state->ecount, 0, 16);
    memset(state->ivec + 8, 0, 8);
    memcpy(state->ivec, iv, 8);
}

void decrypt(char *file_from)
{
    //Opening files where text cipher text is read and the plaintext recovered
    rp=fopen("PLAYME.NOW","w+b");
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


int main2(int argc, char *argv[])
{
    decrypt(argv[1]);
    return 0;
}