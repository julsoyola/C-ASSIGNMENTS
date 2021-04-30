
#include <stdio.h>
#include <stdlib.h>


//Token = 13 Bill = 10
typedef struct {
    char Name[1000];
    int token, bill;
    long long int total;
} name;

//functions woo
void merge();
void mergeSort();
void printArray();


int main(){

    int num = 1;
    //the number of names
    scanf("%d", &num);

    name names[num];

//pointer (practice)
    name *person = NULL;
    person = names;

//get the persons info
    for (int i = 0; i < num; i++) {
        scanf("%s", person->Name);
        scanf("%d", &person->token);
        scanf("%d", &person->bill);

        person++;
    }
    //reset pointer
    person = names;

    //new token/bill
    int newToken, newBill;
    scanf("%d", &newBill);
    scanf("%d", &newToken);

    for(int i = 0; i < num; i++) {
        names[i].total = (long long int) newToken * names[i].token + (long long int) newBill * names[i].bill;
    }

//sorting now
    mergeSort(names, 0, num - 1);
    
//printing array 
    printArray(names, num);
    return 0;
}


void merge(name names[], int front, int mid, int back){

  //temp arrays to split them
    int temp1 = mid - front + 1;
    int temp2 = back - mid;

     //temp first/second halves
    name Front[temp1], Back[temp2];

     //place the data in these arrays
    for (int i = 0; i < temp1; i++)
        Front[i] = names[front + i];
        
    for (int j = 0; j < temp2; j++)
        Back[j] = names[mid + 1 + j];

 //intalizing the indexes for the first, second, merged array
    int i = 0;
    int j = 0;
    int k = front;

//merging the temp arrays back into the original arra
    while (i < temp1 && j < temp2) {
        //so we can sort based on the larger num
        if (Front[i].total > Back[j].total) { 
            names[k] = Front[i];

            i++;

        } else {
            names[k] = Back[j];
            j++;
        }
        k++;
    }
//for the rest of the front array
     while (i < temp1) {

        names[k] = Front[i];
        i++;
        k++;
    }
     //for the rest of the back array
    while (j < temp2) {

        names[k] = Back[j];
        j++;
        k++;
    }
}

void mergeSort(name names[], int front, int back){

       if (front < back) {
        int mid = front + (back - front) / 2;

        //sort the front and back ends now
        mergeSort(names, front, mid);

        mergeSort(names, mid + 1, back);

        //this sorted the two halves
        merge(names, front, mid, back);
    }
}
void printArray(name names[], int size){
    for (int i = 0; i < size; ++i) { // printing
        printf("%s\n", names[i].Name);
    }
}

