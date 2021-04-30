
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef long long ll;
typedef struct Node{
    ll winner, leftSkill, rightSkill;
    ll table;
    struct Node * left;
    struct Node * right;
}Node;

//prototypes
Node * createNode(ll table);
Node * addNode(Node * root, ll table);
ll tagPlayers(Node * root, ll * skills);
ll findMax(ll skill1, ll skill2);
ll findMin(ll skill1, ll skill2);
void destroyNode(Node * root);
void destroyTree(Node * root);
ll findExcite(Node * root, ll * skills, ll excitement);

//global var
int count = 0;

int main()
{
    // Let's declare a tree. It is very similar to a linked list, but
    // we call it root instead of head.
    Node * root = NULL;
    //read the number of players
    ll num;
    scanf("%lld", &num);

    //read the actv line
    ll * fightOrder = (ll*)malloc((num - 1) * sizeof(ll));
    for(ll i = 0; i < num - 1;i++)
    {
        scanf("%lld", &fightOrder[i]);
    }
    //read the skills of each player
    ll * skills = (ll*)malloc(num * sizeof(ll));
    for(int i = 0; i < num; i++)
    {
        scanf("%lld", &skills[i]);
    }

    //add the values to the BST but in reverse order
    for(int i = num - 2; i >= 0;i--)
    {
        root = addNode(root, fightOrder[i]);
    }
    //intalize 
    ll excitement = 0;
    //now that we have our skills, we can find the excitement
    excitement = findExcite(root, skills, excitement);
    //no print function just print the answer once
    printf("%lld\n", excitement);
    printf("\n");
    //now we can free everything, no need to remove them
    free(fightOrder);
    free(skills);
    destroyTree(root);

    return 0;
}
Node * createNode(ll table)
{
    //allocating space for a new node (skill)
    Node * currNode = calloc(1, sizeof(Node));
    currNode->table = table;
    currNode->left = currNode->right = NULL;
    currNode->winner = currNode->leftSkill = currNode->rightSkill = 0;
    return currNode;
}
Node * addNode(Node * root, ll table)
{
    //check if the tree is empty or reach an empty spot (base case)
    if(root == NULL)
    {   //if its empty make a new node
        return createNode(table);
    }
    if(root->table == table)
    {   //we have one number in our tree
        return root;
    }
    /* check to see if the value is less than the current node, if so, go left */
    if(table < root->table)
    {
        root->left = addNode(root->left, table);
    }
    /* check to see if the value is more than the current node, if so, go right */
    if(table > root->table)
    {
        root->right = addNode(root->right, table);
    }
    //tag a number for each table

    //return the root back to main
    return root;
}
//max - min 
ll findExcite(Node * root, ll * skills, ll excitement){
    //broke it into cases
    if(root == NULL) return 0;
    if(root->left == NULL && root->right == NULL){
        root->leftSkill = skills[count++];
        root->rightSkill = skills[count++];
    }
    if(root->left == NULL || root->right == NULL){
        if(root->left == NULL && root->right != NULL){
            root->leftSkill = skills[count++];
            excitement = findExcite(root->right, skills, excitement);
            root->rightSkill = root->right->winner;
        }
        else if(root->right == NULL && root->left != NULL){
            excitement = findExcite(root->left, skills, excitement);
            root->leftSkill = root->left->winner;
            root->rightSkill = skills[count++];
        }
    }
    else if(root->left != NULL && root->right != NULL){
        excitement = findExcite(root->left, skills, excitement);
        excitement = findExcite(root->right, skills, excitement);
        root->leftSkill = root->left->winner;
        root->rightSkill = root->right->winner;
    }
    //once we find who the winner is we can cll the functions to them
    ll max = findMax(root->leftSkill, root->rightSkill);
    ll min = findMin(root->leftSkill, root->rightSkill);
    //now the winner will be set as the max and we can calc the excitement
    root->winner = max;
    return excitement + (max - min);
}
ll findMax(ll skill1, ll skill2)
{ //finidng who the winner is - person w higher skill
    if(skill1 > skill2) return skill1;
    return skill2;

}
ll findMin(ll skill1, ll skill2)
{   //finding the loser
    if(skill1 > skill2) return skill2;
    return skill1;
}
// free fxns
void destroyNode(Node * root)
{
    free(root);
}
// free fxns
void destroyTree(Node * root)
{
    if(root == NULL) return;
    destroyTree(root->left);
    destroyTree(root->right);
    destroyNode(root);
}
