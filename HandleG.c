

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define size 100000



int main(void) {

    char str[size];
    int num;
    int i;

//reads in number of lines
    scanf("%d", &num);

    //loops for each line
    for(int l=0; l <= num; l++)
    {
        //gets the whole string
        fgets(str, size, stdin);

        //loops through the line
        for(i=0; str[i] != '\0'; i++)
         {
            //prints for the first letter
            if(i == 0)
            {
                printf("%c", str[i]);
            }
            //prints for the last letter
             if(i == strlen(str) - 1)
             {
                 printf("%c", str[i]);
             }
             //if the next letter is a space
             if(isspace(str[i + 1]))
            {
            printf("%c", str[i]);
            }
             //last letter
             if(isspace(str[i - 1]))
            {
            printf("%c", str[i]);
            }

         }
    }

    return 0;
}