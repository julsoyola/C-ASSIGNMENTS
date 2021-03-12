#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_CAP 10
#define MAX 10000


// Some typedefs to make life easier
typedef struct Piece Piece;
typedef struct Row Row;
typedef struct Board Board;

// Our structs
struct Piece {
    int row, column, id;
};

struct Row { //row
    int identifier;
    Piece ** arr;
    int size, cap;

};

struct Board {
    Row ** arr;
    int size, cap;
};

// Prototypes
Board * createBoard(); //an array list of any array list
Row * createRow(int);
Piece * createPiece();
void destroyBoard(Board *);
void destroyBoard2(Board *);
void destroyRow(Row *);
void destroyRow2(Row *);
void destroyPiece(Piece *);
void addPieceToRow(Row  *, Piece *);
void addRowToBoard(Board *,  Row  *);
void expandRow(Row *);
void expandBoard(Board *);
Row * findRow(Board *, int);

int main()
{

    //scan in the first piece
    int num_of_pieces;
    int row;
    int column;
    Piece piecesArray[MAX + 1];

    //Build the Board
    Board * board =  createBoard(); //rows
    Board * board2 = createBoard(); //columns
    Piece * piece;
    Row * newRow;
    Row * newRow2;

    //fxns for attack
    Row * search;
    Row * call;

    int maxR = 1000000001, minR = -1, maxColumn = 1000000001, minColumn = -1;
    int attackers[4] = {-1, -1, -1, -1};
    int numAttackers = 0;

    scanf("%d", &num_of_pieces);

    for(int j=1; j < num_of_pieces + 1; j++) {
        scanf("%d", &row);
        scanf("%d", &column);

        piecesArray[j].row = row;
        piecesArray[j].column = column;
        piecesArray[j].id = j;

        //we scanned in the row and column now create the piece
        piece = createPiece(row, column, j);

        //if we don't have one create one
        newRow = findRow(board, row);
        addPieceToRow(newRow, piece);

        //this board is just for the column
        newRow2 = findRow(board2, column);
        addPieceToRow(newRow2, piece);
    }

    for(int l=1; l < num_of_pieces+1; l++)
    {   //  search the rows and call the col
        search = findRow(board,  piecesArray[l].row);
        call = findRow(board2,  piecesArray[l].column);


        //find rows and see where they are in relation to board
        for(int k = 0; k < search->size; k++)
        {       //if its the same we continue
            if(search->arr[k]->column == piecesArray[l].column )
            {
                continue;
            }
            //now if its above we can account it as an attacker
            if(search->arr[k]->column > piecesArray[l].column && search->arr[k]->column < maxColumn )
            {
                maxColumn = search->arr[k]->column;
                attackers[0] = search->arr[k]->id;
            }
            //now if its below we can account it as an attacker
            if(search->arr[k]->column < piecesArray[l].column && search->arr[k]->column > minColumn )
            {
                minColumn = search->arr[k]->column;
                attackers[1] = search->arr[k]->id;
            }
        }
        //find your attackers by C
        for(int k=0; k < call->size; k++)
        {
            if(call->arr[k]->row == piecesArray[l].row)
            {
                continue;
            }
            //now if its above we can account it as an attacker from the column
            if(call->arr[k]->row > piecesArray[l].row && call->arr[k]->row < maxR )
            {
                maxR = call->arr[k]->row;
                attackers[2] = call->arr[k]->id;
            }
            // //now if its below we can account it as an attacker from the Column
            if(call->arr[k]->row < piecesArray[l].row && call->arr[k]->row > minR )
            {
                minR = call->arr[k]->row;
                attackers[3] = call->arr[k]->id;
            }
        }

        for(int i=0; i < 4; i++) {
            if (attackers[i] != -1) {
                numAttackers++;
                //counts how many attackers we have and increment
            }
        }

        //if the number of attackers are 0 printf that # :)
        if(numAttackers > 0)
        {
            printf("%d ", numAttackers);
            for(int j = 0; j < 4; j++)
            {
                if(attackers[j] != -1)
                {
                    printf("%d ", attackers[j]);
                }
            }
        }
        else printf("0");
        //if there are no attackers print 0
        
        maxR = 1000000001;
        minR = -1;
        maxColumn = 1000000001;
        minColumn = -1;
        numAttackers = 0;
        //we have to reintialize everything

        for(int i=0; i < 4; i++) {
            attackers[i] = -1;
        }
        printf("\n");

    }

    destroyBoard(board);
    destroyBoard(board2);
    //clear that memory so comp dont die :)

    return 0;
}

//array 1 creation
Board * createBoard() {
    Board * ret;

    //creating dynamic memory
    ret = (Board *) calloc(1, sizeof(Board));

    ret->size = 0;
    ret->cap = DEFAULT_CAP;
    ret->arr = (Row **) calloc(DEFAULT_CAP, sizeof(Row *));

    return ret;
    //points to board
}
Row * createRow(int identifier){
    Row * ret;

    ret = (Row *) calloc(1, sizeof(Row ));

    //copy the # of pieces
    ret->identifier = identifier;
    ret->size = 0;
    ret->cap = DEFAULT_CAP;
    ret->arr = (Piece **) calloc(DEFAULT_CAP, sizeof(Piece *));

    return ret;
}
Piece *createPiece(int row, int col, int id) {
    Piece * ret;

    ret = (Piece *) calloc(1, sizeof(Piece));

    //copy in the rank, file and id
    ret->row = row;
    ret->column = col;
    ret->id = id;

    return ret;
}
//free the memory belonging to the board
void destroyBoard(Board * board){

    for(int i=0; i < board->size; i++)
    {
        destroyRow(board->arr[i]);

    }
    free(board->arr);
    free(board);
    //delete this last
}
void destroyRow(Row * row){

    for(int i = 0; i <  row->size; i++)
    {

        destroyPiece(row->arr[i]);
    }
    free(row->arr);
    free(row);
}
void destroyPiece(Piece * piece){
    //free the whole thing
    free(piece);
}
void addPieceToRow(Row  * row, Piece * piece) {
    if(row->size == row->cap){
        expandRow(row);
    }

    row->arr[row->size] = piece;
    row->size++;
}
void addRowToBoard(Board * board,  Row * curRow){
    if(board->cap == board->size) {
        expandBoard(board);
    }
    board->arr[board->size] = curRow;
    board->size++;
}
void expandRow(Row * row){
    int newCap = row->cap * 2;

    row->arr = (Piece **) realloc(row->arr, sizeof(Piece *));
    row->cap = newCap;
}
//expanding the board
void expandBoard(Board * board){
    int newCap = board->cap * 2;
    board->arr = (Row **) realloc(board->arr, newCap * sizeof(Row *));
    board->cap = newCap;

}
Row * findRow(Board * board, int identifier){
    Row * ret;

    for(int i=0; i < board->size; i++)
    {
        if(board->arr[i]->identifier == identifier)
        {
            ret = board->arr[i];
            return ret;
        }
    }

    ret = createRow(identifier);
    addRowToBoard(board, ret);

    return ret;
}
void destroyBoard2(Board * board){
    for(int i=0; i < board->size; i++)
    {
        destroyRow(board->arr[i]);

    }
    free(board->arr);
    free(board);
}
//Destroys for the Column Board
void destroyRow2(Row * row){
    free(row->arr);
    free(row);
}
//Destroys for the Column Board