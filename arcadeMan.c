
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define scan 1
#define remove 2
#define print 3
#define exit 0

typedef struct person{
    int Money;
    char * Name;
    struct person * next;
}person;

//prototypes:
person * createNode(int money, char * name);
person * addToTop(int money, char * name, person * current);
void destroyNode(person *Person);
person * removeNode(person *current);
void FindMax(person * current);

//main function
int main()
{
    int choice, money; //which instructions we're gonna use
    char name[21];
   
    scanf("%d", &choice);
    person * current = NULL;

while(choice != 0){

/*switch statement:
    scan: 1 - scans users tokens, name
    remove: 2 - removed the first person to come in
    print: 3 - prints person w/ most $
    exit: 0 - ends code (shop closes)
*/
        switch(choice)
        {
            case scan:
            //read in money, name
            scanf("%d", &money);
            scanf("%s", name);
            //now add them to the front
           current = addToTop(money, name, current);
           scanf("%d", &choice);
            break;

        //remove the last person to come in 
            case remove:
           current = removeNode(current);
           scanf("%d", &choice);
            break;

        //print the person w most $
            case print:
           FindMax(current);    //print the MVP
            scanf("%d", &choice);
            break;

            case exit:
            return 0;
        }
    }
    return 0;
}
person * createNode(int money, char * name)
{
    //allocating space for the current person
     person * currPerson = calloc(1, sizeof(person));
     //allocating for the name
    currPerson->Name= calloc(strlen(name), sizeof(char));
    strcpy(currPerson->Name, name); //copies int currPerson name

    currPerson->Money = money;
    currPerson->next = NULL;
    return currPerson;
}
person * addToTop(int money, char * name, person * current)
{
     //if the list is empty return a new node
    if(current == NULL)
    {
        return createNode(money,name);
    }
    //if the list is not empty we create a new node
    person *currPerson = createNode(money, name);

    // Since it needs to go in front of the head we make the new node's next point to the head
    currPerson->next = current;
    //return the head back to the main function
    return currPerson;
}
void destroyNode(person *Person)
{
    free(Person->Name);
    free(Person);

}
//removing the last person in
person * removeNode(person *current)
{

    //if the list is empty there is nothing to remove
    if(current == NULL)
    {
        return NULL;
    }
     //if theres only one element just free it.
     person * newCurr = current->next;
     destroyNode(current);

     return newCurr;
}
//printing MVP
void FindMax(person * current)
{
    person * firstPerson = current;

//if the current is not null that means theres something inside
    while(current != NULL){
        if(firstPerson->Money < current->Money){
            firstPerson= current;
        }
        current = current->next;
    }
//prints person w the most money
printf("%s\n", firstPerson->Name);
}
