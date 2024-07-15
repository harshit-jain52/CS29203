// 22CS10030 Harshit Jain
// Lab Test 2 Question 2

#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node *left;
    struct node *right;
} node;

node *getMin(node *root);
node *standardDelete(node *root, int val);
node *newNode(int val);

node *insertNode(node *root, int val) // O(depth)
{
    if (root == NULL)
        root = newNode(val);
    else if (val >= root->data)
        root->right = insertNode(root->right, val);
    else if (val < root->data)
        root->left = insertNode(root->left, val);

    return root;
}

int search(node* root, int x) // O(depth)
{
    int ct = 0;

    if(root == NULL) return ct;

    if(root->data <= x){
        ct += (root->data==x) + search(root->right,x);
    }
    else{
        ct += search(root->left,x);
    }

    return ct;
}

node *deleteNode(node *root, int val) // O(depth)
{
    if (root == NULL)
        return root;

    if (val > root->data)
        root->right = deleteNode(root->right, val);
    else if (val < root->data)
        root->left = deleteNode(root->left, val);
    else
    {
        if (root->left == NULL && root->right == NULL)
        {
            free(root);
            return NULL;
        }
        if (root->left == NULL)
        {
            node *tmp = root;
            root->right = deleteNode(root->right,val);
            root = root->right;
            free(tmp);
        }
        else if (root->right == NULL)
        {
            node *tmp = root;
            root = root->left;
            free(tmp);
        }
        else
        {   
            root->right = deleteNode(root->right,val);
            
            if(root->right){
                node *MinInRight = getMin(root->right);                     // finds the smallest node in the right branch
                root->data = MinInRight->data;                              // copy data
                root->right = standardDelete(root->right, MinInRight->data); // delete the min node in right
                // last step should be done by standard delete operation to avoid deletion of multiple occurences of MinInRight
            }
            else if(root->left){
                node *tmp = root;
                root = root->left;
                free(tmp);
            }
            else{
                free(root);
                return NULL;
            }
        }
    }
    return root;
}

void printSorted(node *root) // In-Order Traversal of BST; O(N)
{
    if (root == NULL)
        return;

    printSorted(root->left);
    printf("[ %d ]\t", root->data);
    printSorted(root->right);
}

int main(){
    int n,i,dat;
    node* tree = NULL;

    /*
    // HARD-CODED INPUT
    int arr[]={20, 10, 30, 5, 15, 20, 32, 10, 15, 20, 12, 18, 25, 16, 20, 28};
    n = 16;
    for(i =0;i<n;i++){
        tree = insertNode(tree,arr[i]);
    }
    
    printf("\n");
    printSorted(tree);

    printf("\n%d",search(tree,20));
    printf("\n%d",search(tree,10));
    printf("\n%d",search(tree,30));
    printf("\n%d",search(tree,5));
    printf("\n%d",search(tree,15));
    printf("\n%d",search(tree,32));
    printf("\n%d",search(tree,12));
    printf("\n%d",search(tree,18));
    printf("\n%d",search(tree,16));

    tree = deleteNode(tree,20);
    printf("\n");
    printSorted(tree);
    printf("\n%d",search(tree,20));

    tree = deleteNode(tree,15);
    printf("\n");
    printSorted(tree);
    printf("\n%d",search(tree,15));

    tree = deleteNode(tree,18);
    printf("\n");
    printSorted(tree);
    printf("\n%d",search(tree,18));
    */

    // INTERACTIVE INPUT
    printf("\nNumber of nodes in initial BST: ");
    scanf("%d",&n);
    printf("Enter %d Nodes: ",n);
    for(i =0;i<n;i++){
        scanf("%d",&dat);
        tree = insertNode(tree,dat);
    }
    printf("\nInOrder of the input BST:\n");
    printSorted(tree);

    int ch, x;
    while(1){
        printf("\n\n1. Search\n2. Insert\n3. Delete\n4. Quit\n");
        printf("Enter choice: ");
        scanf("%d",&ch);

        if(ch==1){
            printf("\nData to search for: ");
            scanf("%d",&x);
            printf("No. of occurences of %d: %d",x,search(tree,x));
        }
        else if(ch==2){
            printf("\nData to insert: ");
            scanf("%d",&x);
            tree = insertNode(tree,x);

            printf("\nInOrder of the BST after insertion:\n");
            printSorted(tree);
        }
        else if(ch==3){
            printf("\nData to delete: ");
            scanf("%d",&x);
            tree = deleteNode(tree,x);

            printf("\nInOrder of the BST after deletion\n");
            printSorted(tree);
        }
        else if(ch==4){
            printf("\nExit\n");
            break;
        }
        else{
            printf("\nInvalid Choice\n");
        }
    }
}

node *newNode(int val)
{
    node *vertex = (node *)malloc(sizeof(node));
    vertex->data = val;
    vertex->left = NULL;
    vertex->right = NULL;

    return vertex;
}

node *getMin(node *root) // O(depth)
{
    if (root->left != NULL)
        return getMin(root->left);
    else
        return root;
}

node *standardDelete(node *root, int val) // O(depth)
{
    if (root == NULL)
        return root;

    if (val > root->data)
        root->right = standardDelete(root->right, val);
    else if (val < root->data)
        root->left = standardDelete(root->left, val);
    else
    {
        if (root->left == NULL && root->right == NULL)
        {
            free(root);
            return NULL;
        }
        if (root->left == NULL)
        {
            node *tmp = root;
            root = root->right;
            free(tmp);
        }
        else if (root->right == NULL)
        {
            node *tmp = root;
            root = root->left;
            free(tmp);
        }
        else
        {
            node *MinInRight = getMin(root->right);
            root->data = MinInRight->data;
            root->right = standardDelete(root->right, MinInRight->data);
        }
    }

    return root;
}