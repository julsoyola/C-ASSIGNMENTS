#include <stdio.h>
#include <stdlib.h>


typedef long long ll;
typedef struct Node{
    ll key;
    struct Node * left;
    struct Node * right;
    struct Node * parent;
}Node;

//prototypes
Node * createNode(ll key);
Node * addNode(Node * root, int parent, int key);
int findExcite(Node * root, int actv[], int * excitement, int skill[], int n);
void getPostorder(Node * root, int *arr, int depth);
void getLevel(Node * root, int *arr, int depth, int level);
int maxDepth(Node * root);
void initialize(int *arr, int dep);
int  activations(int *a1, int *a2, int size);

int main()
{
    // Let's declare a tree. It is very similar to a linked list, but
    // we call it root instead of head.
    Node * root = NULL;
    //read the number of players
    int num;
    scanf("%d", &num);

    int parent[num - 1];
    int skill[num + 1]; 
    skill[0] = -1;

    int spot[num - 1];
    int table = -1;

    //scan in 2nd line, the parents
    for (int i = 0; i < num - 1; i++)
    {
        scanf("%d", &parent[i]);
        spot[i] = i + 1;
        //if we reach a -1 we know that will be the last one, or root
        if (parent[i] == -1)
            table = i + 1;
    }
    for (int i = 1; i <= num; i++)
    {
        //read in each of their skills
        scanf("%d", &skill[i]);
    }
    root = addNode(root, -1, table);

    //adding it in
    int tempVar[num - 1];
    for (int i = 0; i < num - 1; i++)
    {
        tempVar[i] = 0;
    }
    tempVar[table - 1] = 1;
    //now we can keep track of the sums and get the min
    int count = 1;
    while (count < num)
    {
        for (int j = 0; j < num - 1; j++)
        {
            //case to check if we're on the champ
            if (parent[j] == -1)
                continue;
            if (tempVar[parent[j] - 1] == 1)
            {
                tempVar[spot[j] - 1] = 1;
                count++;
                //now we can add it on our tree and check
                addNode(root, parent[j], spot[j]);
            }
        }
    }
    int length = maxDepth(root);
    int actv[num - 1][num - 1];
    //so we can keep count
    int index = 0;
    for (int i = 0; i < num - 1; i++)
    {
        initialize(actv[i], num - 1);
    }

    getPostorder(root, actv[index], num - 1);
    index++;

    printf("\n");

    for (int i = 1; i <= length; i++)
    {
        getLevel(root, actv[index], num - 1, i);
    }
    index++;

    //heap time; time to check the best order
    int checkExcite[num - 1];
    int checkActv[num -1];

     for (int i = 0; i < num - 1; i++)
    {
        checkActv[i] = actv[0][i];
    }
    int bestExcitment = findExcite(root, actv[0], checkExcite, skill, num);
    //our checks
    int invalid = 0;
    //more cases to check each option possible
    for (int i = 1; i < index; i++)
    {
        int excitement[num - 1];
        int tempExcite = findExcite(root, actv[i], excitement, skill, num);
        //now we can compare our possibilities and compare their excitment
        if (tempExcite > bestExcitment)
        {
            invalid = 1;
        }
        else if (tempExcite == bestExcitment)
        {
            int current = activations(checkExcite, excitement, num - 1);
            if (current == 2)
                invalid = 1;
        }
        if (invalid == 1)
        {
            for (int k = 0; k < num - 1; k++)
            {
                checkExcite[k] = excitement[k];
                checkExcite[k] = actv[i][k];
            }
        }
        invalid = 0;
    }
    //now we know which one has the best option so we print that one out
    for (int i = 0; i < num - 1; i++)
    {
        printf("%d ", checkActv[i]);
    }
    printf("\n");
    return 0;
}

Node * createNode(ll key)
{
    //allocating space for a new node (skill)
    Node * currNode = calloc(1, sizeof(Node));
    currNode->key = key;
    currNode->left = currNode->right = currNode->parent = NULL;
   
    return currNode;
}
Node * addNode(Node * root, int parent, int key)
{
    //check if the tree is empty or reach an empty spot (base case)
    if(root == NULL)
      //if its empty make a new node
        return createNode(key);
    if(key < root->key)
    {
        Node *lchild = addNode(root->left, parent, key);
         root->left = lchild;
        lchild->parent = root;
    }
    /* check to see if the value is more than the current node, if so, go right */
    if(key > root->key)
    {
        Node *rchild = addNode(root->right, parent, key);
        root->right = rchild;
        rchild->parent = root;
    }
    //tag a number for each table
    //return the root back to main
    return root;
}
//min
int findExcite(Node * root, int actv[], int *excitement, int skill[], int n)
{
    int open[n + 1];
    int Excitement = 0;
    open[0] = -1;

    //broke it into cases

    for (int i = 0; i < n; i++)
    {
        open[i] = 1; 
    }
    for (int i = 0; i < n - 1; i++)
    {
        int j1 = actv[i];
        while (open[j1] != 1 && j1 > 0)
        {
            j1--; 
        }
        int left = skill[j1]; 
        int j2 = actv[i] + 1;
        while (open[j2] != 1 && j2 <= n + 1)
        {
            j2++; 
        }
        int right = skill[j2]; 
        Excitement += abs(left - right);
        excitement[i] = abs(left - right);
        if (left < right)
        {
            open[j1] = 0; 
        }
        else
        {
            open[j2] = 0; 
        }
    }
    //now the winner will be set as the max and we can calc the excitement
    return Excitement;
}
void getPostorder(Node * root, int *arr, int depth)
{
    if (root == NULL)
        return;
    //recursive
    getPostorder(root->left, arr, depth);
    getPostorder(root->right, arr, depth);
    for (int i = 0; i < depth; i++)
    {
        if (arr[i] == -1)
        {
            arr[i] = root->key;
            break;
        }
    }
}
void getLevel(Node * root, int *arr, int depth, int level)
{
    if (root == NULL)
        return;
    if (level == 1)
    {
        for (int i = depth - 1; i >= 0; i--)
        {
            if (arr[i] == -1)
            {
                arr[i] = root->key;
                break;
            }
        }
    }
     else if (level > 1)
    {
        getLevel(root->left, arr, depth, level - 1);
        getLevel(root->right, arr, depth, level - 1);
    }
}
int maxDepth(Node * root)
{
    //looking at the rows and col
    if (root == NULL)
        return 0;
    else
    {
        int lDepth = maxDepth(root->left);
        int rDepth = maxDepth(root->right);

        if (lDepth > rDepth)
            return (lDepth + 1);

        else
            return (rDepth + 1);
    }
}
void initialize(int *arr, int dep)
{
    for (int i = 0; i < dep; i++)
    {
        arr[i] = -1;
    }
}
int activations(int *a1, int *a2, int size)
{
    //checking and finding the least actv orders
    int sum1 = 0;
    int sum2 = 0;

    for (int i = 0; i < size; i++)
    {
        sum1 += a1[i];
        sum2 += a2[i];
        if (sum1 > sum2)
            return 2;

        else if (sum2 > sum1)
            return 1;
    }

  return 0;
}
