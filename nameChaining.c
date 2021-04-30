#include <stdio.h>
#include <string.h>


#define size 100
#define MAX 12
#define GO 1
#define STOP 0

/* Note:
An if statement will count 0 as false and 1 as true.
if(1) will always be true and if(0) will always be false
*/

int findPretty();
int rec();


int main(void) {
    int num;
    int used[MAX];
    int current = 0;
    //2d array to store my str
    char str[MAX][size];
    char arr[MAX][size];

    //Scan in the number of words
    scanf("%d", &num);

    //in the used array set to 0 in perm
    for(int i = 0; i < num; i++){
        used[i] = 0;
    }
    //scan in words
    for(int i = 0; i < num; i++){
        scanf("%s", &str[i]);
    }
    //rec function goes here
    rec(str, arr, current, num, used);

    return 0;
}

int findPretty(char arr[][size], int num){

    for(int i = 0; i < num - 1; i++){

        if(arr[i][strlen(arr[i]) - 1] != arr[i + 1][0])
            //out of order elements
            return STOP;
    }
    return GO; //it works
}

int rec(char str[][size], char arr[][size], int current, int num, int * used)
{
    if(current == num)
    {
        if(findPretty(arr, num))
        {
            for(int i = 0; i < num; i++)
            {
                printf("%s ", arr[i]);
            }
            return GO;
        }
        else
            return STOP;
    }
    else
    {
        for(int j = 0; j < num; j++)
        {
            if(used[j] == 0)
            {
                strcpy(arr[current], str[j]);
                used[j] = 1;

                if(rec(str, arr, current + 1, num, used))

                    return GO;

                used[j] = 0;
            }
        }
        return 0;
    }
}