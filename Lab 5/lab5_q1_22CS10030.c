// 22CS10030 Harshit Jain
// Assignment 5 Question 1

#include <stdio.h>
#include <stdlib.h>
#define MAXLEN 10000
#define datatype node*

typedef struct node
{
    int data;
    struct node *left;
    struct node *right;
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
node *deserialize(int arr[], int n);
int serialize(node * root, int arr[]);
void inOrder(node *vertex);

// Function that does the work
node* keepRange(node* root, int l, int r){
    if(root==NULL) return NULL;

    while(root!=NULL && (root->data< l || root->data >r)){
        while(root!=NULL && root->data < l){
            node* tmp = root;
            root = root->right;
            free(tmp);
        }

        while(root!=NULL && root->data > r){
            node* tmp = root;
            root = root->left;
            free(tmp);
        }
    }
    if(root!=NULL){
        root->left = keepRange(root->left,l,r);
        root-> right = keepRange(root->right,l,r);
    }

    return root;
}

int main(){
    int n, i;
    int input[MAXLEN], output[MAXLEN];
    
    printf("\nNo. of inputs: ");
    scanf("%d",&n);

    printf("\nInput Tree: \n");

    for(i=0;i<n;i++){
        scanf("%d",&input[i]);
    }

    int lo,hi;
    printf("min = ");
    scanf("%d",&lo);
    printf("max = ");
    scanf("%d",&hi);

    node* root = deserialize(input, n); // Create BST from input array
    
    // inOrder(root);
    // printf("\n\n");
    
    root = keepRange(root, lo, hi); // Modify the Tree according to instructions

    // inOrder(root);
    // printf("\n\n");

    int len= serialize(root, output); // Create output array for the BST
    
    printf("\nModified Tree: \n");
    for (i = 0; i < len; i++)
    {
        printf("%d ",output[i]);
    }
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

    return vertex;
}

node *deserialize(int arr[], int n){
    int idx = 0;
    node* root = newNode(arr[idx++]);

    queue q = init();
    q = enqueue(q , root);
    int sz=1, tmpsize;

    while(!isEmpty(q) && idx<n){
        tmpsize = 0;
        while(sz--){
            front(q)->left = newNode((idx<n)?arr[idx++]:-1);
            front(q)->right = newNode((idx<n)?arr[idx++]:-1);

            if(front(q)->left){
                q =enqueue(q,front(q)->left);
                tmpsize++;
            }
            if(front(q)->right){
                q =enqueue(q,front(q)->right);
                tmpsize++;
            }

            q = dequeue(q);
        }
        sz = tmpsize;
    }

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

void inOrder(node *vertex)
{
    if (vertex == NULL)
        return;

    inOrder(vertex->left);
    printf("%d ", vertex->data);
    inOrder(vertex->right);
}