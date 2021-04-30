#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char ** argv) {
    char Key[3000];
    char Plain[3000];
    int i = 0, j;

    FILE * keyFile = fopen(argv[1], "r");
    FILE * plainFile = fopen(argv[2], "r");

    //store in the first characters
   int kFile = getc(keyFile);
   int pFile = getc(plainFile);

    //store in the whole .txt file

    while(kFile != EOF)
    {
        if(isalpha(kFile))
        {
            Key[i] = tolower(kFile);
            i++;
        }

       kFile = getc(keyFile);
    }
    Key[i] = '\0';
    i = 0;
    while(pFile!= EOF)
    {
        if(isalpha(pFile))
        {
            Plain[i] = tolower(pFile);
            i++;
        }

        pFile =  getc(plainFile);
    }
    //so we can use the
    Plain[i] = '\0';


    int plainLength = strlen(Plain);
    int  keyLength = strlen(Key);

    //:(
    if(plainLength < 512){

        for( i = plainLength; i < 512; i++)
        {
            Plain[i] = 'x';
        }
        Plain[i] = '\0';
    }
    Plain[512] = '\0';

    plainLength = strlen(Plain);

    char newKey[plainLength], cipherText[plainLength];

    //generating a new Key
    for(i = 0, j = 0; i < plainLength; i++){

        if(j == keyLength) {

            j = 0;
        }
        newKey[i] = Key[j];
        j++;
    }
    newKey[i] = '\0';


    //encryption
    for(i = 0; i  < plainLength; i++)
    {
        cipherText[i] = (((Plain[i] - 'a') + (newKey[i] - 'a')) % 26 + 'a');
    }
    cipherText[i] = '\0';

    int index = 0;

    //OUTPUT
    printf("\n\nVigenere Key:\n");
    while(index < keyLength)
    {
        if(index % 80 == 0)
        {
            printf("\n");
        }
        printf("%c", Key[index]);
        index++;

    }
    index = 0;
    printf("\n\n\nPlaintext:\n");
    while(index < plainLength)
    {
        if(index % 80 == 0)
        {
            printf("\n");
        }
       printf("%c", Plain[index]);
        index++;

    }
    index = 0;
    printf("\n\n\nCiphertext:\n\n");
    while(index < plainLength)
    {
        printf("%c", cipherText[index]);
        index++;
        if(index % 80 == 0)
        {
            printf("\n");
        }
    }
    printf("\n");
    return 0;
}
