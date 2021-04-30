#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


void readFile();
void displayData();
void outputFile();

//data structure
typedef struct produceItemS {
    char produce[20];
    char type[20];
    char soldBy[20];
    float price;
    int quantityInStock;
    struct produceItemS *next;

}produceItem;

produceItem* head;
produceItem* items[26];

//main fxn
int main() {
    int choice;
    head = NULL;

    struct produceItem *n;

    while(true) {

        //printfstatements

        printf("\nList Operations\n");
        printf("############################\n");
        printf("1. Stock Produce Department\n");
        printf("2. Display Produce Inventory\n");
        printf("3. Export Produce Inventory\n");
        printf("4. Exit Program\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice){

            case 1:
                readFile();
                break;

            case 2:
                displayData();
                break;

            case 3:
                outputFile();
                break;

            case 4:
                return 0;
                break;




        }


    }
    return 0;
}

void nodefxn(produceItem* temp,char produce[], char type[], char soldBy[], float price, int quantityInStock ) {


    //place the data
    strcpy(temp->produce, produce);
    strcpy(temp->type, type);
    strcpy(temp->soldBy, soldBy);
    temp->price = price;
    temp->quantityInStock = quantityInStock;
}

void readFile() {

    printf("\nBeginning to Read File...\n");
    FILE* FileName;
    int i;
    int number = 25;
    char *produce;
    char *type;
    char *soldBy;
    float price;
    int quantityInStock;
    FileName = fopen("Assignment7Input.txt", "r");

    if(FileName  == NULL )
    {
        perror("ERROR WHILE OPENING FILE\n");
        exit(0);
    }
    else
    {
        printf("Sucessfully opened file \n");
    }

    for(i=0; i < 26; i++)
    {
        items[i] = (produceItem*)malloc(sizeof(produceItem));
    }

    while(number >= 0) {

        char buff[255];

        fgets(buff, 255, FileName);

        produce = (strtok(buff, ","));
        type = (strtok(NULL, ","));
        soldBy = (strtok(NULL, ","));

        price = atof(strtok(NULL, ","));
        //tokening int

        quantityInStock = atoi(strtok(NULL, ","));

        nodefxn(items[number], produce, type, soldBy, price, quantityInStock );

        if(number - 1 == 0) {

            items[number - 1]->next = NULL;
        }
            //
        else
        {
            items[number] -> next = items[number -1];
        }
        //sub. the # to put items in the right order
        number = number - 1;
    }

}
void displayData() {
    int i;
    printf("================================================================\n");
    printf(" Item #    Produce         Type          Sold By          Price\n ");
    printf("================================================================\n");

    //formatting : )
    for(i = 0; i < 26; i++) {

        printf("%5d%6s", i + 1, " ");
        printf("%-13s", items[i] -> produce);
        printf("%-17s", items[i] -> type);
        printf("%-17s", items[i] -> soldBy);
        printf("%-9.2lf", items[i] -> price);
        printf("%d\n", items[i] -> quantityInStock);
    }
}
void outputFile() {

    //creating VAR

    printf("\nBegin writing file..\n");
    FILE *FileName;
    int i;

    FileName = fopen("Assignment7Output.txt", "w+");

    printf("====================================================\n");
    printf(" Item #    Produce     Type     Sold By    Price\n ");
    printf("====================================================\n");

    for(i = 0; i <26; i++)
    {
        fprintf(FileName, "%5d%6s", i+1," ");
        fprintf(FileName, "%-13s", items[i] -> produce);
        fprintf(FileName, "%-17s", items[i] -> type);
        fprintf(FileName, "%-17s", items[i] -> soldBy);
        fprintf(FileName, "%-9.2lf", items[i] -> price);
        fprintf(FileName, "%d\n", items[i] -> quantityInStock);
    }

    //closing the file


    fclose(FileName);
    printf("File finished \n");
}
