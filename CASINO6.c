
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SLOTS 1
#define SCRATCH 2
#define BLACKJACK 3
#define FACES 13
#define SUITS 4
#define CLUBS 0
#define DIAMONDS 1
#define HEARTS 2
#define SPADES 3
#define BUST 21
#define ONE 1
#define TWO 2
#define FIVE 5
#define BONUS 20
#define EXIT 4


#define $

void welcomescreen();

// welcome Screen

int displayMenu();

void clearScreen();
int playSlots(int);
int playScratchOffs(int);
int playBlackJack(int);
char randomSymbol();
void printDeck();
void initializeDeck();
void initializeUsed();
int deal();
int results();
int cashOneDollar();
int cashTwoDollar();
int cashFiveDollar();
char getBonus();
int cards;

// game of SO



struct OneDollar {
    int winNumber;
    int numbers[5];
    float prizes[5];
    char bonus[2];
};
struct TwoDollar {
    int winNumbers[2];
    int numbers[10];
    float prizes[10];
    char bonus[2];
};
struct FiveDollar {
    int winNumbers[4];
    int numbers[12];
    float prizes[12];
    char bonus[4];

};


struct OneDollar createScratchOffOne(struct OneDollar oneSO);

void displayScratchOffOne(struct OneDollar oneSO);

struct TwoDollar createScratchOffTwo(struct TwoDollar twoSO);

void displayScratchOffTwo(struct TwoDollar twoSO);

struct FiveDollar createScratchOffFive(struct FiveDollar fiveSO);

void displayScratchOffFive(struct FiveDollar fiveSO);



// main function

int main() {

    srand(time(0));
    // random fxn to gen. true random numbers
    int game;
    int cash = 1000;
    int play = 1;
// change above to test diff. cash amounts plz
    welcomescreen();

    while (play) {
        clearScreen();
        game = displayMenu();
        clearScreen();

        switch (game) {
            case SLOTS:
                cash = playSlots(cash);
                break;
            case SCRATCH:
                cash = playScratchOffs(cash);
                break;
            case BLACKJACK:
                cash = playBlackJack(cash);
                break;
            case EXIT:
                game = 0;
                return 0;
        }
        printf("Your Cash Balance is %d\n", cash);
        printf("Wanna play another game?? 1 = yes , 0 = no\n");
        scanf("%d", &play);
    }
    return 0;

};

void welcomescreen() // allows us to see the first screen
{
    printf("\t\t###################################################\n");
    printf("\t\t###################################################\n");
    printf("\t\t#######\t\t\t\t\t\t\t\t\t###########\n");
    printf("\t\t#######\t\t\tKnights Casino\t\t\t###########\n");
    printf("\t\t###################################################\n");
    printf("\t\t###################################################\n");
}


void clearScreen() { // that goes away and now we can hit enter
    printf("\t\tHit enter to continue\n");
    char cl;

    scanf("%c", &cl);

    // system("cls"); for Windows; Below is unix

    system("Clear");
}


int displayMenu() {
    //  game is your userselect

    int userSelect;
    do { // now user choses the game
        printf("Select a game to play by entering the number next to the game\n");
        printf("1. Slots\n");
        printf("2. Scatch Offs\n");
        printf("3. Black Jack\n");
        printf("4. Quit Game\n");

        scanf("%d", &userSelect);

    } while (userSelect < SLOTS || userSelect > EXIT);
    return userSelect;

}

int playSlots(int cash) {
    // your bets
    const int BET = 5;
    // what u wanna pay
    const int MATCH_TWO = 5;
    const int MATCH_THREE = 50;

    // CONTROL YOUR LOOP
    int play = 1;
// THESE ARE UR RAND. SYMBOLS

    char symOne;
    char symTwo;
    char symThree;


    printf("Let's play the slot machines!!\n\n");
    printf("Your cash balance is $%d. The bet is $%d. ^ o ^\n", cash, BET);
    printf("** Match two symbols to win!!** $%d.\n\n", MATCH_TWO);
    printf("Match all three symbols to win $%d.\n\n", MATCH_THREE);

    if (cash < BET) {

        printf("You are out of cash, you cannot play\n\n");
        play = 0;
    }
// keep playing until user doesn't
    while (play != 0) {
        // PLACE $5
        cash -= BET;

        // GEN. THREE SYMBOLS
        printf("**** Spinning ***\n\n");
        symOne = randomSymbol();
        symTwo = randomSymbol();
        symThree = randomSymbol();

        printf("%c %c %c\n\n", symOne, symTwo, symThree);

//three symbols matched
        if (symOne == symTwo && symOne == symThree) {
            cash = cash + 50;
            printf(" You made $50!!\n\n");
            // fix me
        }
            // match 2
        else if (symOne == symTwo || symOne == symThree || symTwo == symThree) {
            cash = cash + 5;
            printf(" You made $5 woo!!\n\n");
        } // match none
        else {

            cash = cash + 0;
            printf("you made $0, try again next time :(\n\n");
        }

        // update user w/ how much $ they have
        printf("You made $%d.Let's Keep This Up!\n\n", cash);
// ask user if they wanna play, if they have less then 5 they can't
        if (cash >= 5 && play == 1) {
            printf("Do you wanna spin again?\n\n");
            printf("1. To continue\n");
            printf("2. To Stop\n");
            scanf("%d", &play);
        } else {

            break;

        }
    }


    printf("\t\t\t\tThank You For Playing :)\t\t\t\n\n");
    printf("\t\t\t\tYour balance is %d\n\t\t\t", cash);
    return cash;
}


char randomSymbol() {
    const int SYMBOLS = 6;
    char symbols[] = {'$', '%', '&', '#', '@', '!', '\0'};
    char symbol;
    int num;

    num = rand() % 6;

    switch (num) {
        case 0:
            symbol = symbols[0];
            break;
        case 1:
            symbol = symbols[1];
            break;
        case 2:
            symbol = symbols[2];
            break;
        case 3:
            symbol = symbols[3];
            break;
        case 4:
            symbol = symbols[4];
            break;
        case 5:
            symbol = symbols[5];
            break;
    }
    return
            symbol;
}
// ur at 8.h in project

int playScratchOffs(int cash) {


    printf(" Welcome, You Are In The Scratch Off Game!\n");
    printf("Ready?\n");

    int type;
    int count;
    int c;
    struct OneDollar oneSO;
    struct TwoDollar twoSO;
    struct FiveDollar fiveSO;
    int play =1;


    printf("Let's Play!\n");
    printf("Players can select from three options\n");
    printf("One Dollar, Two Dollar, and Five Dollars tickets\n");
    printf("Prizes are based on the tickets you select\n");
while (play==1) {

    printf("Which ticket would you like to select?\n");
    printf("1 = One Dollar\t\t2 = Two Dollar\t\t5 = Five Dollar");
    scanf("%d", &type);

    printf("How many scratch offs would you like to get?\n");
    scanf("%d", &count);

    printf("Getting your scratch offs...\n");
// This is for the number of scratch offs
    for (c = 0; c < count; ++c) {

        switch (type) {

            case ONE:

                    if (cash > ONE) {
                        cash -= (type);


                        oneSO = createScratchOffOne(oneSO);
                        displayScratchOffOne(oneSO);
                        cash += cashOneDollar(oneSO);

                    }
                    else {
                        printf("Sorry You Are Out of Money $$\n");
                        c = count;

                    }

                break;

            case TWO:

                    if (cash > TWO) {
                        cash -= (type );
                        twoSO = createScratchOffTwo(twoSO);
                        displayScratchOffTwo(twoSO);
                        cash += cashTwoDollar(twoSO);


                    }
                    else {
                        printf("Sorry You Are Out of Money $$\n");
                        c = count;


                }
                break;

            case FIVE:

                    if (cash > FIVE) {
                        cash -= (type);
                        fiveSO = createScratchOffFive(fiveSO);
                        displayScratchOffFive(fiveSO);
                        cash += cashFiveDollar(fiveSO);

                    }

                    else {
                        printf("Sorry You Are Out of Money $$\n");
                        c = count;

                    }
                    break;

                }
        }

   printf("Your Cash Balance is %d\n", cash);
    printf("Would you like to play again? 0 = no , 1 = yes\n");
    scanf("%d", &play);
}
    return cash;
}
struct OneDollar createScratchOffOne(struct OneDollar oneSO) {


    const int SYMS = 2;
    const int NUMS = 5;
    const int BASE = 20;
    int play = 1;


    const char SYMBOLS[] = {'$', '%', '&', '#', '@', '!'};
    int sym;
    int n;
int usedSyms[6] =  {0,0,0,0,0,0 } ;
int used = 0;


    for (n = 0; n < SYMS; ++n) {
        oneSO.winNumber = rand() % (BASE + 1);

    }
    // 0 is false 1 is true

    for (n = 0; n < NUMS; ++n)
    {
        oneSO.numbers[n] = rand() % (BASE + 1);
    }

    // For loop to generate the prizes. We need 10.
    for (n = 0; n < NUMS; ++n)
    {
        oneSO.prizes[n] = (float)(rand() % 150 + 5);
    }
    for (n = 0; n < SYMS; ++n) {


        used = 0;
        while(used == 0) {
            sym = rand() % 6;
            if(usedSyms[sym] == 0) {
                usedSyms[sym] = 1;
                used = 1;
                break;
            }

        }

        switch (sym) {

            case 0:
                oneSO.bonus[n] = SYMBOLS[0];
                break;
            case 1:
                oneSO.bonus[n] = SYMBOLS[1];
                break;
            case 2:
                oneSO.bonus[n] = SYMBOLS[2];
                break;
            case 3:
                oneSO.bonus[n] = SYMBOLS[3];
                break;
            case 4:
                oneSO.bonus[n] = SYMBOLS[4];
                break;
            case 5:
                oneSO.bonus[n] = SYMBOLS[5];
                break;


        }
    }
    return oneSO;

}

void displayScratchOffOne(struct OneDollar oneSO) {
    const int SYMS = 2;   // for number of bonus symbols
    const int NUMS = 5; //5 for number of player numbers and prizes

    int n; //for looping

    printf("+------------------------------------------+\n");
    printf("| WINNING NUMBERS%6s", " ");


    printf("%12d", oneSO.winNumber);


    printf("%8s|\n|%42s|\n"," ", " ");
    printf("| Your Numbers%29s|\n|", " ");

    for(n = 0; n < NUMS; n++) {

        printf("%8d", oneSO.numbers[n]);

    }
    printf("  |\n");
    printf("|%42s|\n", " "); //display the blank lines of the scratch off ticket
    printf("| Prizes%35s|\n", " ");
    printf("|%42s|\n"," ");

    for(n = 0; n < NUMS; n++) {

        printf("%8.2f", oneSO.prizes[n]);

    }
    printf("\n%42s |\n", " ");
    printf("| SYMBOLS%34s|\n", " ");
    printf("|%42s|\n", " ");


    for(n = 0; n < SYMS; n++) {
        printf("%6c", oneSO.bonus[n]);

    }

    printf("\n");

}
struct TwoDollar createScratchOffTwo(struct TwoDollar twoSO) {

    const int SYMS = 2;
    const int NUMS = 10;
    const int BASE = 30;

    const char SYMBOLS[] = {'$', '%', '&', '#', '@', '!'};
    int sym;
    int n;
    int usedSyms[6] =  {0,0,0,0,0,0 } ;
    int usedNums[6] =  {0,0,0,0,0,0 } ;
    int used = 0;
int num;

    for (n = 0; n < SYMS; ++n) {

        used = 0;
       while(used == 0) {

           num =  rand() % (BASE + 1);

           if(usedNums[n] == 0){
               usedNums[n] = 1;

               if(n == 1 ) {
                   twoSO.winNumbers[n] = rand() % (BASE + 1);

                   while(twoSO.winNumbers[n] == twoSO.winNumbers[0]) {
                       twoSO.winNumbers[n] = rand() % (BASE + 1);
                       break;
                   }

               }
               else {
                   twoSO.winNumbers[n] = num;

               }
              used = 1;

           }
           break;
       }
    }
    for (n = 0; n < NUMS; ++n) {
        twoSO.numbers[n] = rand() % (BASE + 1);

    }
    for (n = 0; n < NUMS; ++n) {
        twoSO.prizes[n] = (float) (rand() % 150 + 5);
    }

    for (n = 0; n < SYMS; ++n) {

        used = 0;
        while(used == 0) {
            sym = rand() % 6;
            if(usedSyms[sym] == 0) {
                usedSyms[sym] = 1;
                used = 1;
                break;
            }

        }


        switch (sym) {

            case 0:
                twoSO.bonus[n] = SYMBOLS[0];
                break;
            case 1:
                twoSO.bonus[n] = SYMBOLS[1];
                break;
            case 2:
                twoSO.bonus[n] = SYMBOLS[2];
                break;
            case 3:
                twoSO.bonus[n] = SYMBOLS[3];
                break;
            case 4:
                twoSO.bonus[n] = SYMBOLS[4];
                break;
            case 5:
                twoSO.bonus[n] = SYMBOLS[5];
                break;
        }

    }
    return twoSO;
}
void displayScratchOffTwo(struct TwoDollar twoSO) {

    const int SYMS = 2;
    const int NUMS = 10;
    const int BREAK = 4;
    int n;

    printf("+------------------------------------------+\n");
    printf("| WINNING NUMBERS%6s", " ");

    for(n = 0; n < SYMS; n++) {
        printf("%6d", twoSO.winNumbers[n]);

    }
    printf("%8s|\n|%42s|\n"," ", " ");
    printf("| Your Numbers%29s|\n|", " ");

    for(n = 0; n < NUMS; n++) {

        printf("%8d", twoSO.numbers[n]);
        if(n == BREAK)
            printf("\n|");

    }
    printf("  |\n");
    printf("|%42s|\n", " "); //display the blank lines of the scratch off ticket
    printf("| Prizes%35s|\n", " ");
    printf("|%42s|\n"," ");

    for(n = 0; n < NUMS; n++) {

        printf("%8.2f", twoSO.prizes[n]);
        if(n == BREAK)
            printf("\n|");

    }
    printf("\n%42s |\n", " ");
    printf("| SYMBOLS%34s|\n", " ");
    printf("|%42s|\n", " ");


    for(n = 0; n < SYMS; n++) {
        printf("%6c", twoSO.bonus[n]);

    }
    printf("\n");
    printf("+------------------------------------------+\n");


}

struct FiveDollar createScratchOffFive(struct FiveDollar fiveSO) {
    const int SYMS = 4;
    const int NUMS = 12;
    const int BASE = 50;


    const char SYMBOLS[] = {'$', '%', '&', '#', '@', '!', '^', '*'};
    int sym;
    int n;
    int usedSyms[8] =  {0,0,0,0,0,0,0,0 } ;
    int usedNums[4] =  {0,0,0,0} ;
    int used = 0;
    int num;


    for (n = 0; n < SYMS; ++n) {


        used = 0;
        while(used == 0) {
           num =  rand() % (BASE + 1);
            usedNums[n] = 1;
            // if the number is not being used in the array
            // we mark it as used
            if(n == 1) {
                fiveSO.winNumbers[n] =  rand() % (BASE + 1);
                // when the number is the same we loop it again until
                //  they're diff.

                while(fiveSO.winNumbers[n] == fiveSO.winNumbers[0]) {
                    fiveSO.winNumbers[n] =  rand() % (BASE + 1);
                    break;
                }
            }
         else if(n == 2) {
                fiveSO.winNumbers[n] =  rand() % (BASE + 1);
             while(fiveSO.winNumbers[n] == fiveSO.winNumbers[0] || fiveSO.winNumbers[n] == fiveSO.winNumbers[1]) {
                 fiveSO.winNumbers[n] = rand() % (BASE + 1);
                 break;
                 // checking to see if they're duplicates in array 0 & 1 if so randomize again
             }

         }
         else if(n == 3) {
                fiveSO.winNumbers[n] =  rand() % (BASE + 1);
                while(fiveSO.winNumbers[n] == fiveSO.winNumbers[0] || fiveSO.winNumbers[n] == fiveSO.winNumbers[1]|| fiveSO.winNumbers[n] == fiveSO.winNumbers[2]) {
                    fiveSO.winNumbers[n] = rand() % (BASE + 1);
                    break;
         }

        }
         else {
                fiveSO.winNumbers[n] = num;
            }
         used = 1;
            break;
        }


    }
    for (n = 0; n < NUMS; ++n) {
        fiveSO.numbers[n] = rand() % (BASE + 1);
    }

    // For loop to generate the prizes. We need 10.
    for (n = 0; n < NUMS; ++n) {
        fiveSO.prizes[n] = (float) (rand() % 250 + 5);
    }
    for (n = 0; n < SYMS; ++n) {

        sym = rand() % 6;
        if(usedSyms[sym] == 0) {
            usedSyms[sym] = 1;
            used = 1;
            break;
        }

        switch (sym) {

            case 0:
                fiveSO.bonus[n] = SYMBOLS[0];
                break;
            case 1:
                fiveSO.bonus[n] = SYMBOLS[1];
                break;
            case 2:
                fiveSO.bonus[n] = SYMBOLS[2];
                break;
            case 3:
                fiveSO.bonus[n] = SYMBOLS[3];
                break;
            case 4:
                fiveSO.bonus[n] = SYMBOLS[4];
                break;
            case 5:
                fiveSO.bonus[n] = SYMBOLS[5];
                break;
            case 6:
                fiveSO.bonus[n] = SYMBOLS[6];
                break;
            case 7:
                fiveSO.bonus[n] = SYMBOLS[7];
                break;


        }
    }
    return fiveSO;
}
void displayScratchOffFive(struct FiveDollar fiveSO) {

    const int SYMS = 4;
    const int NUMS = 12;
    const int BREAK = 4;
    int n;
    printf("+------------------------------------------+\n");
    printf("| WINNING NUMBERS", " ");

    for(n = 0; n < SYMS; n++) {
        printf("%6d", fiveSO.winNumbers[n]);

    }
    printf("%2s|\n|%42s|\n"," ", " ");
    printf("| Your Numbers%29s|\n|", " ");

    for(n = 0; n < NUMS; n++) {

        printf("%8d", fiveSO.numbers[n]);
        if(n == BREAK)
            printf("\n|");
        else if (n== BREAK *2)
            printf("%10s|\n", " ");


    }
    printf("                   |\n");
    printf("|%42s|\n", " "); //display the blank lines of the scratch off ticket
    printf("| Prizes%35s|\n", " ");
    printf("|%42s|\n"," ");

    for(n = 0; n < NUMS; n++) {

        printf("%8.2f", fiveSO.prizes[n]);
        if(n == BREAK)
            printf("    \n|");
        else if (n== BREAK *2)
            printf("%10s|\n|", " ");

    }
    printf("\n%42s |\n", " ");
    printf("| SYMBOLS%34s|\n", " ");
    printf("|%42s|\n", " ");


    for(n = 0; n < SYMS; n++) {
        printf("%6c", fiveSO.bonus[n]);


    }
    printf("\n");
    printf("+------------------------------------------+\n");
}

int cashOneDollar(struct OneDollar oneSO){
    const int SYMS =2; // value 2 for number of bonus symbols
    const int NUMS =5; // value 5 for number of player numbers and prizes
    float cash;
    int n;
    char bonus;
    bonus = getBonus(ONE);

    printf("Bonus Symbol %c\n", bonus);

    for(n=0; n < NUMS; ++n) {
// Compare each of the player’s numbers to the winning number
        if (oneSO.numbers[n] == oneSO.winNumber) {
            cash = cash + oneSO.prizes[n];
        }
    }
        for (n = 0; n < SYMS; ++n) {
            if (bonus == oneSO.bonus[n]) {
                cash = BONUS + cash;
            }
        }
        printf("You've earned $%.2f\n", cash);

        return cash;
}
int cashTwoDollar(struct TwoDollar twoSO) {
    const int WINS = 2; //value 2 for the number of winning numbers
    const int SYMS = 2; //value 2 for number of bonus symbols
    const int NUMS = 5; //with value 5 for number of player numbers and prizes

    float cash;
    int w;
    int n;
    char bonus;
    bonus = getBonus(TWO);

    printf("Bonus Symbol %c\n", bonus);

    for(w =0; w < WINS; ++w ) {
        for (n = 0; n < 10; ++n) {
            if (twoSO.numbers[n] == twoSO.winNumbers[n]) {
                cash = cash + twoSO.prizes[n];
            }

        }
    }
for(n=0; n < SYMS; ++n) {
    if(twoSO.bonus[n] == bonus) {
cash = BONUS + cash;

    }

}
    printf("You Earned $%.2f\n", cash);
    return cash;
}
int cashFiveDollar(struct FiveDollar fiveSO) {

    const int WINS =4;
    const int SYMS = 4;
    const int NUMS = 12;
    float cash;
    int w;
    int n;
    char bonus;
    bonus = getBonus(FIVE);

    printf("Bonus Symbol %c\n", bonus);
    for(w = 0; w < WINS; ++w) {
        for(n=0; n < NUMS; ++n) {
            if(fiveSO.numbers[n] == fiveSO.winNumbers[n]) {
                cash = cash + fiveSO.prizes[n];
            }
        }
for(n =0; n< SYMS; ++n) {
    if(fiveSO.bonus[n] == bonus) {
        cash = BONUS + cash;
    }

}

    }

    printf("You Earned $%.2f\n", cash);
    return cash;
}
char getBonus(int type) {
    const int ONE_TWO = 6;
    const int FIVE_RAND = 8;
    const char SYMBOLS[] = {'$', '%', '&', '#', '@', '!', '^', '*', '^'};
    char bonus;
    int sym;
    if (type == ONE || type == TWO) {
        sym = rand() % 8;

        switch (sym) {


                case 0:
                    bonus = SYMBOLS[0];
                break;

                case 1:
                    bonus = SYMBOLS[1];
                break;

                case 2:
                    bonus = SYMBOLS[2];
                break;

                case 3:
                    bonus = SYMBOLS[3];
                break;

                case 4:
                    bonus = SYMBOLS[4];
                break;

                case 5:
                    bonus = SYMBOLS[5];
                break;

                case 6:
                    bonus = SYMBOLS[5];
                break;

                case 7:
                    bonus = SYMBOLS[5];
                break;

            }
        }
else if(type == FIVE) {
        sym = rand() % 8;

        switch (sym) {


            case 0:
                bonus = SYMBOLS[0];
                break;

            case 1:
                bonus = SYMBOLS[1];
                break;

            case 2:
                bonus = SYMBOLS[2];
                break;

            case 3:
                bonus = SYMBOLS[3];
                break;

            case 4:
                bonus = SYMBOLS[4];
                break;

            case 5:
                bonus = SYMBOLS[5];
                break;

            case 6:
                bonus = SYMBOLS[5];
                break;

            case 7:
                bonus = SYMBOLS[5];
                break;
        }
}
return bonus;
    }


int playBlackJack(int cash) {

    printf("Welcome, You Are In The BlackJack Game");
    // BET AMOUNT
    const int BET = 10;
// BLACKJACK CONSTS
    const int MIN_HIT = 16;
    const int HIT = 1;
    const int STAND = 0;

    //LOOP CONTROL
    int play = 1; //continue playing
    int choice = 0; //player can hit or stand
    int bust = 0;

    int player = 0; //keeps track of score
    int dealer = 0;

    char deck[SUITS][FACES]; //THIS IS THE DECK
    int dealt[SUITS][FACES]; //WHICH CARDS ARE DEALT

// 7.1 in project
    printf("Let's play BLACK JACK! \n\n");
    printf("Your Cash balance is $%d\n", cash);
    printf("The bet is $%d\n", BET);
    printf("Dealer must HIT if their score is 16 or less\n");
    printf("Dealer must STAND if their score is 17 or higher\n");
    printf("If the player wins the hand, you get $20 :)\n");
    printf("If the Dealer wins the hand, your $10 bet is lost :(\n");
    printf("If it is a PUSH, you keep your $%d bet >:)\n", BET);
    printf("Good Luck!!!\n");

    clearScreen();

    if (cash < BET) {
        printf("Sorry, you have ran out of $, you don't have enough to play\n");
        return cash;
    }
    initializeUsed(dealt);

    printf("Shuffling the cards.....\n");
    initializeDeck(deck);

    printf("Here's the deck....\n");
    printDeck(deck);

    clearScreen();

    printf("\n\n Dealing.....\n");

    while (play == 1) {
        printf("\nPlayer's cash is $%d\n\n", cash);

        if (cash < BET) {
            printf("Player does not have enough money to play!\n");
            play = 0;
            continue;
        }

        // place the bet
        // 7.iii on word
        cash -= BET;
        int player = 0;
        int dealer = 0;
        int bust = 0;
//help
        player += deal(deck, dealt);
        player += deal(deck, dealt);

        printf("\nPlayer's score %d\n", player);
        dealer += deal(deck, dealt);
        dealer += deal(deck, dealt);
        printf("Do you want to STAND OR HIT (0 = STAND 1= HIT)\n");
        scanf("%d", &choice);

        // keep looping until player busts or stands

        while (choice == HIT && player < BUST) {
            player += deal(deck, dealt);


            printf("\nPlayer's score %d\n", player);


            // is player busts 21 they win
            if (player > BUST) {
                bust = 1;
                printf("\n Sorry! Player Busted. Dealer Wins!\n");

                // break loop
                break;
            } else {
                printf("\nAnother Card? (0 = STAND, 1 = HIT\n");
                scanf("%d", &choice);
            }

        } // HIT WHILE LOOP SO PLAYER CAN CHOOSE
        if (bust > 0) {
            printf("\nPlayer, wanna play again?? (0 = NO, 1 = YES\n");
            scanf("%d", &play);

            //now clear screen after each hand
            clearScreen();
            continue;
        } else {
            if (dealer <= MIN_HIT) {
                choice = HIT;
            } else {
                choice = STAND;
            }
            // now keep dealing
            while (choice == HIT) {
                dealer += deal(deck, dealt);
                if (dealer <= MIN_HIT) {

                    choice = HIT;
                } else {
                    choice = STAND;
                }
            }
        }
        printf("\nDealer's score %d\n", dealer);
        cash += results(player, dealer);

        printf("\nPlayer, do you wanna play again?\n");
        printf("0 = NO, 1 = YES");
        scanf("%d", &play);

        clearScreen();

    }
    printf("\nThank you for playing BLACK JACK\n");
    printf("Your cash out is %d\n\n", cash);
    return cash;
}

int results(int playScore, int dealScore) {
// payouts
    const int WIN = 20;
    const int PUSH = 10;
    const int LOSE = 0;

    if (dealScore > BUST) {
        printf("Dealer Busted\n");
        return PUSH;
    }
        // IF ITS A PUSH PLAYER GETS THEIR BET
    else if (playScore == dealScore) {
        printf("It's a PUSH\n");
        return PUSH;
    } else if (playScore > dealScore) {
        printf("Player WINS!\n");
        return WIN;
    } else {
        printf("Dealer WINS the hand. Sorry try again next time\n");
        return LOSE;
    }
}

int deal(char deck[SUITS][FACES], char dealt[SUITS][FACES]) {
    // MAX # OF CARDS IS 52
    const int MAX = 52;

    // helps see if card was used
    int used = 0;
    int score;

    // randoms
    int face;
    int suit;

    if(cards == MAX); {
        cards = 0;
        initializeUsed(dealt);
    }
    while (!used) {
        suit = rand() % SUITS;
        face = rand() % FACES;

        // if card hasn't been dealt
        if (dealt[suit][face] == 0) {
            //ends loop to see check unused card
            used = 1;
            dealt[suit][face] = 1;
            cards++;
        }
    }

    switch (face) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
            score = face + 2;
            break;
        case 8:
        case 9:
        case 10:
        case 11:
            score = 10;
            break;
        case 12:
            score = 11;
            break;
    }
    return score;

}

void initializeUsed(char used[SUITS][FACES]) {
    int s;
    int f;
    for (s = 0; s < SUITS; s++) {

        for (f = 0; f < FACES; f++) {
            used[s][f] = 0;
        }
    }


}

void initializeDeck(char deck[SUITS][FACES]) {

    const char face[] = {'2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A'};

    int i;
    int j;

    for (i = 0; i < SUITS; i++) {
        for (j = 0; j < FACES; j++) {
            deck[i][j] = face[j];
        }
    }
}

void printDeck(char deck[SUITS][FACES]) {
    int s;
    int f;

    for (s = 0; s < SUITS; s++) {
        for (f = 0; f < FACES; f++) {
            switch (s) {
                case CLUBS:
                    printf("%c of CLUBS\n", deck[s][f]);
                    break;
                case DIAMONDS:
                    printf("%c of Diamonds\n", deck[s][f]);
                    break;
                case HEARTS:
                    printf("%c of Hearts\n", deck[s][f]);
                    break;
                case SPADES:
                    printf("%c of Spades\n", deck[s][f]);
                    break;

            }

        }
    }

}

