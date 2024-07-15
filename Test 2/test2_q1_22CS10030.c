// 22CS10030 Harshit Jain
// Lab Test 2 Question 1

#include <stdio.h>
#include <stdlib.h>
#define MAXLEN 10000
#define datatype node*

int abs(int x){
    if(x<0) return -x;
    return x;
}

typedef struct node
{
    int data;
    struct node *left;
    struct node *right;
    struct node *parent;
} node;

// Queue Implementation starts
typedef struct
{
    datatype arr[MAXLEN]; // maximum size of the queue is MAXLEN-1
    int front;
    int back;
} queue;

queue init();
int isEmpty(queue Q);
int isFull(queue Q);
datatype front(queue Q);
queue enqueue(queue Q, datatype elem);
queue dequeue(queue Q);
// Queue Implementation ends

// Utility Functions for Binary Tree
node *newNode(int val);
node *deserialize(int arr[], int n, node* leaves[], int *numOfLeaves);
int serialize(node * root, int arr[]);

int main(){
    int n, i;
    int input[MAXLEN], output[MAXLEN], numofLeaves;
    node* leaves[MAXLEN];

    printf("\nSize of input array: ");
    scanf("%d",&n);

    printf("\nInput Tree: \n");

    for(i=0;i<n;i++){
        scanf("%d",&input[i]);
    }

    // Create Binary Tree from input array and store leaves
    node* root = deserialize(input, n, leaves, &numofLeaves);

    //printf("\n%d\n",numofLeaves);

    // Start from leaves and move upwards
    int diff, op = 0;
    queue q = init();
    for(i=0;i<numofLeaves;i++){
        q = enqueue(q,leaves[i]);
    }

    while(!isEmpty(q)){
        // root will be handled automatically as sum of weights = number of nodes
        if(front(q)->parent) // handling all nodes except root
        {
            diff = front(q)->data-1;
            op+=abs(diff);

            front(q)->data = 1;
            front(q)->parent->data+=diff;
            q = enqueue(q,front(q)->parent);
        }
        q = dequeue(q);
    }

    printf("\nMinimum no. of operations: %d\n",op);

    int len = serialize(root, output); // Create output array for the Binary tree

    for(i = len-1;i>=0;i--) // Remove Trailing -1's
    {
        if(output[i]!=-1){
            len = i+1;
            break;
        }
    }

    printf("\nFinal Tree: \n");
    for(i=0;i<len;i++){
        printf("%d ",output[i]);
    }
    printf("\n");
}

queue init()
{
    queue Q;
    Q.front = 0;
    Q.back = MAXLEN - 1;

    return Q;
}

int isEmpty(queue Q)
{
    return (Q.front == (Q.back + 1) % MAXLEN);
}

int isFull(queue Q)
{
    return (Q.front == (Q.back + 2) % MAXLEN);
}

datatype front(queue Q)
{
    if (isEmpty(Q))
    {
        printf("\nfront: Empty Queue\n");
        return NULL;
    }

    return Q.arr[Q.front];
}

queue enqueue(queue Q, datatype elem)
{
    if (isFull(Q))
    {
        printf("\nenqueue: Full Queue\n");
        return Q;
    }

    Q.back = (++Q.back) % MAXLEN;
    Q.arr[Q.back] = elem;
    return Q;
}

queue dequeue(queue Q)
{
    if (isEmpty(Q))
    {
        printf("\ndequeue: Empty Queue\n");
        return Q;
    }

    Q.front = (++Q.front) % MAXLEN;
    return Q;
}

node *newNode(int val)
{   
    if(val==-1) return NULL;

    node *vertex = (node *)malloc(sizeof(node));
    vertex->data = val;
    vertex->left = NULL;
    vertex->right = NULL;
    vertex->parent = NULL;

    return vertex;
}

node *deserialize(int arr[], int n, node* leaves[], int* numOfleaves){
    int idx = 0,l=0;
    node* root = newNode(arr[idx++]);

    queue q = init();
    q = enqueue(q , root);
    int sz=1, tmpsize;

    while(!isEmpty(q)){
        tmpsize = 0;
        while(sz--){
            front(q)->left = newNode((idx<n)?arr[idx++]:-1);
            front(q)->right = newNode((idx<n)?arr[idx++]:-1);

            if(front(q)->left ==NULL && front(q)->right==NULL){
                leaves[l++] = front(q);
            }
            if(front(q)->left){
                front(q)->left->parent = front(q);
                q =enqueue(q,front(q)->left);
                tmpsize++;
            }
            if(front(q)->right){
                front(q)->right->parent = front(q);
                q =enqueue(q,front(q)->right);
                tmpsize++;
            }
            q = dequeue(q);
        }
        sz = tmpsize;
    }
    
    *numOfleaves = l;
    return root;
}

int serialize(node * root, int arr[]){
    int idx =0;
    node* curr = root;
    
    queue q = init();
    q = enqueue(q,curr);

    int sz = 1, tmpsize;

    while(!isEmpty(q)){
        tmpsize = 0;
        while(sz--){
            curr = front(q);
            q = dequeue(q);

            if(curr==NULL){
                arr[idx++] = -1;
            }
            else{
                arr[idx++] = curr->data;
                
                q = enqueue(q, curr->left);
                tmpsize++;

                q = enqueue(q, curr->right);
                tmpsize++;
            }
        }
        sz = tmpsize;
    }

    return idx;
}