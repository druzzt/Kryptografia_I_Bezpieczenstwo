//@Usage: ./decipher2 file1 file2 file3 ... fileToDecrypt
//@Description: Displays most probable output \
    for last file from program's arguments. \
    Files should be encrypted with identical key. \
    With number of files- power of probability levels up. \
    ..st pro....y .or.. ..ly ..th my ....ples \
	index: 208836
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define HLEN 22
#define KLEN 8192
FILE *fp[22];
int decimed[HLEN][KLEN];
int decimed2[HLEN][KLEN];
void
clear()
{
    const char* CLEAR_SCREE_ANSI = "\e[1;1H\e[2J";
    write(STDOUT_FILENO,CLEAR_SCREE_ANSI,12);
}

int main(int argc, char* argv[]){
    /* CHECKING FILES */
    char kry[HLEN][KLEN], i=1, forsucc[HLEN], c=0;
    int j=0, len[HLEN], longest[HLEN], Oo=0;
    //printf(">>>>>>>>%d files to decode.\n",argc-1);
    for(i=1;i<HLEN;i++){ len[i]=longest[i]=0;
        for(j=0;j<KLEN;j++) decimed[i][j]=decimed2[i][j]=0;}
    for(i=1;i<argc;i++){
        fp[i]=fopen(argv[i],"r");
        if(!fp[i]){ fprintf(stderr,
                            "decipher2: Can't open %s file from in.list!", argv[i]);
            forsucc[i]=0;
        }
        else forsucc[i]=1;
    }
    /* GETTING AND CONVERTING THEM TO BINARY */
    int word[HLEN];
    for (i=1; i<argc; i++){
       // printf("<%s> file %d:\t",argv[i],i);
        if(forsucc[i]==1){
            word[i]=0;
            int bit2=0;
            j=0;
            int eightbit=1;

            while(((c) = getc(fp[i])) != EOF){ // VERY BAD. who cares
                if(c!=' '){
                // printf("(%d)",eightbit);
                if(eightbit==1){
                        if(c=='1'){
                        decimed[i][j]=128;
                    }else{
                        ;
                    }eightbit=2;
                }else if(eightbit==2){
                    if(c=='1'){
                        decimed[i][j]+=64;
                    }else{
                        ;
                    }eightbit=3;
                }else if(eightbit==3){
                    if(c=='1'){
                        decimed[i][j]+=32;
                    }else{
                        ;
                    }eightbit=4;
                }else if(eightbit==4){
                    if(c=='1'){
                        decimed[i][j]+=16;
                    }else{
                        ;
                    }eightbit=5;
                }else if(eightbit==5){
                    if(c=='1'){
                        decimed[i][j]+=8;
                    }else{
                        ;
                    }eightbit=6;
                }else if(eightbit==6){
                    if(c=='1'){
                        decimed[i][j]+=4;
                    }else{
                        ;
                    }eightbit=7;
                }else if(eightbit==7){
                    if(c=='1'){
                        decimed[i][j]+=2;
                    }else{
                        ;
                    }eightbit=8;
                }else if(eightbit==8){
                    if(c=='1'){
                        decimed[i][j]+=1;
                    }else{
                        ;
                    }eightbit=1;
                    j++;
                    word[i]++;
                }}
 
            }
            //printf("\t<= %d words\n",word[i]);
        }
    }
    /*
    for(i=1;i<argc;i++){printf("#\t<file %d>: ",i);
        for(j=0;j<word[i];j++){
            printf("%d,",decimed[i][j]);
        }printf("<END OF FILE %d>\n", i);
    }// DISPLAYING ENCRYPTED MESSAGES. */
    
    int out[HLEN][KLEN];
    //printf("Distribution table(after xoring all ciphers with message to decrypt):\n");
    for(i=1;i<argc;i++){
        //printf("%d>\t",i);
        for(j=0;j<word[argc-1]/*/*24*/;j++){
            out[i][j]=decimed[i][j]^decimed[argc-1][j];
   //             printf("%d ",out[i][j]);
            
        }
   //     printf("\n");
    }
    
    
    int y[HLEN][257]; // na y[i][0] wsadzam dlugosc tablicy dla ulatwienia
    int y1[255][HLEN][128];
    int k;
    int keys[255][HLEN][128];
    int searchingFor=0;
    for(i=1;i<argc;i++){ y[i][0]=0; for(j=0;j<256;j++)for(k=0;k<129;k++) y1[j][i][k]=0; keys[j][i][k]=0;}
    
    
    int g,h,J,ii,jj,s,gg,kk;
    for(j=0;j<word[argc-1];j++){
        s=1;
        for(i=1;i<argc;i++){
            for(g=0;g<256;g++){
                h=g^out[i][j];
                if((h>=32 && h<91) || (h>96 && h<123)){
                    y1[j][i][0]++;
                    y1[j][i][y1[j][i][0]]=h;
                }
            }
        }
        for(i=1;i<argc;i++){
            searchingFor=y1[j][i][s];
            for(ii=1;ii<argc;ii++){
                for(jj=0;jj<y1[j][i][0];jj++){
                    if(searchingFor==y1[j][ii][jj] && i!=ii){
                        keys[j][i][0]++;
                        keys[j][i][keys[j][i][0]]=searchingFor;
                       
                    }
                }
            }
        }
    }
    
    
    jj=1;
    for(i=1;i<argc;i++)for(j=0;j<256;j++)for(k=0;k<129;k++)y1[j][i][k]=0;
    for(j=0;j<word[argc-1];j++){
        for(i=1;i<argc;i++){
            for(gg=1;gg<keys[j][i][0];gg++){
                int found=0;
                for(ii=1;ii<y1[j][i][0];ii++){
                    if(y1[j][i][ii]==keys[j][i][gg]){
                        found=1;
                        break;
                    }
                }
                if(found==0){
                    y1[j][i][0]++;
                    y1[j][i][y1[j][i][0]]=keys[j][i][gg];
                }
            }
        }
    }
    int seek[128];
    int found=0;
    for(j=0;j<word[argc-1];j++){printf("\n%d>",j);
        for(i=1;i<argc;i++){//printf("~%d:",i);
            for(gg=1;gg<y1[j][i][0];gg++){
                if(y1[j][i][gg]==32||y1[j][i][gg]==46||
                   (y1[j][i][gg]>96&&y1[j][i][gg]<123)||
                   (y1[j][i][gg]>63 && y1[j][i][gg]<91) ){
                    printf("%c",y1[j][i][gg]);
                }
            }
        }
    }
     printf("\n");

    
    /*/ just comment this line or delete star so OUTPUT comes on screen.
    for(i=1;i<argc;i++){
        printf("%d>>%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\t%c\n",i,75^out[i][0],
               105^out[i][1],110^out[i][2],103^out[i][3],97^out[i][4],32^out[i][5],82^out[i][6],
               117^out[i][7],115^out[i][8],105^out[i][9],110^out[i][10],32^out[i][11],114^out[i][12],
               111^out[i][13],98^out[i][14],105^out[i][15],32^out[i][16],115^out[i][17],101^out[i][18],
               108^out[i][19],102^out[i][20],105^out[i][21],101^out[i][22],32^out[i][23],122^out[i][24],
               46^out[i][38]);
    }
    //*/
   
    for (i=1;i<argc;i++){ fclose(fp[i]); } // closing all file pointers. they won't be needed now.
    printf("\n");
    return 0;
        /*   "Kinga Rusin robi selfie z wielbłądem..."  */
}
