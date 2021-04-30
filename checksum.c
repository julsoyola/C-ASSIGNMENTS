
/*=============================================================================|
 Assignment:  HW 02–Calculating the 8, 16, or 32 bit checksum for a
|                             given input file|
|    Author:  Juliana Oyola
|    Language:  C
|
|   To Compile: checksum.c
|
|   To Execute:  java Hw02textfile.txtchecksum_size
|      where the files in the command line are in the current directory.
|
|   The text file contains text is mixed case with spaces,punctuation,
|   and is terminated by the hexadecimal ‘0A’, inclusive.
|                          (The 0x’0A’ is included in the checksum calculation.)
|
|                    The checksum_size contains digit(s) expressing the checksum size
|                    of either 8, 16, or 32 bits
|
|   Class:  CIS3360 -Security in Computing –Spring 2021
|   Instructor:  McAlpin
|   Due Date:  per assignment
|
+=============================================================================*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// functions prototypes
void CheckSumFile(char *file, int size);
void SolveCheckSum(int size, char *String, unsigned int long *check);
unsigned int long paddingSolver(char *String, int SumSize);

// main function
int main(int argc, char *argv[])
{     printf("\n");
    // Declare the string fileName to store the name of the file
    char *fileName = malloc(sizeof(char) * 30);

    // Declare the variable to store the checksum bit size
    int bitSize;

    // copy the name of the file into fileName
    strcpy(fileName, argv[1]);

    // checkSumBits variable
    bitSize = atoi(argv[2]);

    //check if its 8, 16, 32
    if(bitSize == 8 || bitSize == 16 || bitSize == 32)
    {
        switch(bitSize)
        {
            case 8:
                CheckSumFile(fileName, bitSize);
                break;

            case 16:
                CheckSumFile(fileName, bitSize);
                break;

            case 32:
                CheckSumFile(fileName, bitSize);
                break;
        }
    }
    return 0;
}
void CheckSumFile(char *file, int checkSumSize)
{
    //size is the checkSum Size
    //file pinter

    FILE *fileInput;

    //declare variables
    int charSize = 0; //character values in string
    int charCnt = 0;

    int wordSize = checkSumSize / 8 + 1;
    int i = 0, j = 0, k = 0;

    // allocate memory for the checksum
    unsigned int long *checksum = calloc(1, sizeof(unsigned int long));
    char *txtFile = malloc(sizeof(char) * wordSize);

    //open and read the file
    fileInput = fopen(file, "r");
    //cases to see if files are being read
    if (fileInput == NULL)
    {
        printf("Can not open file :(\n"); return;
    }
//if it opens compute the checksum
//make sure to read until end of file
    while (charSize != EOF)
    {
        //check to see if its one letter
        if (wordSize - i == 1)
        {
            //null character
            txtFile[i] = '\0';
            //print the string from the file
            printf("%s", txtFile);

            //now that we have our string, do the checksum computation
            SolveCheckSum(checkSumSize, txtFile, checksum);
            //increment so it keeps going
            j++;
            i = 0; //reset the var to 0;
            //formating: if its 80 char new line it
            if (j * (wordSize - 1) == 80)

                printf("\n");

        }
            //if it has more than one
        else
        { // read the character from the fileInput
            charSize = fgetc(fileInput);
            // if the charValue is EOF we need to check the bitSize
            if (charSize == EOF)
            {
                if (checkSumSize == 16 || checkSumSize == 32)
                {   //see if its less then the bitSize, the characters
                    if (wordSize - i != 1 && wordSize - i != wordSize)
                    {
                        k = 0; //setting to 0
                        while (wordSize - i != 1 && wordSize - i != wordSize)
                        {
                            txtFile[i] = 'X';
                            i++;
                            k++;
                        }

                        txtFile[i] = '\0'; //termination character again
                        //display the string from the text file
                        printf("%s", txtFile);
                        //call the fxn to commpute the Checksum
                        SolveCheckSum(checkSumSize, txtFile, checksum);
                        j++;
                        //increment the character cnt
                        charCnt += k - 1;
                        i = 0; //reset the var againe

                        //formating: if its 80 char new line it
                        if (j * (wordSize - 1) == 80)
                            printf("\n");
                    }
                        //now we can break
                    else
                        break;
                }
                else
                    break;
            }
            else
                txtFile[i] = charSize;
            charCnt++;
            i++;
        }
    }
    // close the input file
    fclose(fileInput);
    printf("\n");
    //print the results
    printf("%2d bit checksum is %8lx for all %4d chars\n", checkSumSize, *checksum, charCnt);
}

void SolveCheckSum(int checkSumSize, char *string, unsigned int long *checksum)
{
    unsigned int long BitsMask;

    BitsMask = paddingSolver(string, checkSumSize);

    //Caluclate checksum

    *checksum = BitsMask + *checksum;

    *checksum = *checksum << (64 - checkSumSize);

    *checksum = *checksum >> (64 - checkSumSize);

}
unsigned int long paddingSolver(char *string, int SumSize)
{
    int i = 0;
    unsigned int long BitsMask;
    BitsMask= string[i];
    SumSize -= 8;

    while (SumSize != 0)
    {
        BitsMask= (BitsMask << 8) + string[i + 1];
        SumSize -= 8;
        i++;
    }
    // return
    return BitsMask;
}
/*=============================================================================
|     I [Juliana] ([5061477]) affirm that this program is
| entirely my own work and that I have neither developed my code together with
| any another person, nor copied any code from any other person, nor permitted
| my code to be copied  or otherwise used by any other person, nor have I
| copied, modified, or otherwise used programs created by others. I acknowledge
| that any violation of the above terms will be treated as academic dishonesty.
+=============================================================================*/


