#include <stdio.h>


int BinarySearch();


int main(){

    //call the search
    BinarySearch();

    return 0;
}

int BinarySearch(){
    int MAX;
    char str[50];
    int guess1 = 0;
    int guess2 = 0;
    int mid = 1;
    int MIN = 1;

    // Max Number of possible guesses
    scanf("%d", &MAX);

    //newline character
    fgets(str, 50, stdin);

    //we wanna keep it looping until we finally hit a Game Over
    for(int i = 0; i < MAX; i++ ) {
        //store the first guess
        guess1 = ((MAX + MIN)/ 2);
        printf("%d\n", guess1);

        fflush(stdin);

        //check if yes or no change
        fgets(str, 50, stdin);
        if (str[0] == 'Y' || str[0] == 'y'){
            return 0;
        }
        //if no change then print 
        if (str[4] == 'N' || str[4] == 'n'){

            guess1 = (guess1 + guess2) / 2;
            printf("%d\n", guess1);
            fflush(stdin);
            fgets(str, 50, stdin);
            return 0;
        }
        //store a second guess so we can check high and lows
        guess2 =  guess1 + 1;
        printf("%d\n", guess2);
        fflush(stdin);

        //scan in the lines
        fgets(str, 50, stdin);
        if (str[0] == 'N' || str[0] == 'n') {

        }
        //if yes or game over end
        if (str[0] == 'Y' || str[0] == 'y' || str[0] == 'G' || str[0] == 'g') {

            return 0;
        }
        //if no change find the mid between the two
        if (str[4] == 'N' || str[4] == 'n') {
            printf("%d\n", (guess1 + guess2) / 2);
            fflush(stdin);
        }
        //check if colder if so go down
        if (str[4] == 'C' || str[4] == 'c') {
            MAX = guess1 - 1;
        }
        //check if its warmer if it is then search up
        if (str[4] == 'W' || str[4] == 'w') {
            MIN = guess2 + 1;
        }
    }
    return 0;
}
