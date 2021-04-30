#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define size 1000000

int main()
{
    char **str;
    int i;
    char name[i];
    int num;

    //reads in number of lines
    scanf("%d", &num);
    getchar();

//creating space for the stings
    str = (char **)malloc(num *sizeof(char *));

    for (i = 0; i < num; i++)
         str[i] = (char *)realloc(str[i], sizeof(char)* size);

    //loops for each line
    for(i = 0; i < num; i++)
    {
        //scan in the string
        fgets(str[i] , size, stdin);

        //gets length for each str
        name[i] = strlen(str[i]) - 1;
    }
    for(i = 0; i < num; i++)
    {
        if(name[i] == 1)
        {
            printf("%c\n", str[i][0]);
            return 0;
        }
        //printing first char
        printf("%c", str[i][0]);

        for(int j = 0; j < name[i]; j++)
        {
            //if it reaches a space, it prints the previous and first char
            if(str[i][j] == ' ')
            {
                printf("%c", str[i][j - 1]);
                printf("%c", str[i][j + 1]);
            }
        }
        //the last char of the str
        printf("%c\n", str[i][name[i] - 1]);
    }
    
    free(str);
    
    return 0;
}
