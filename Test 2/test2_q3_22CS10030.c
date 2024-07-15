// 22CS10030 Harshit Jain
// Lab Test 2 Question 3

#include <stdio.h>
#include <stdlib.h>

int size = 0;

void swap(int *x, int *y)
{
    int tmp = *x;
    *x = *y;
    *y = tmp;
}

// Helper Functions of Heap
int Root() { return 1; }
int parent(int i) { return i / 2; }
int leftChild(int i) { return 2 * i; }
int rightChild(int i) { return 2 * i + 1; }
int hasParent(int i) { return i != Root(); }
int isValidNode(int i) { return i <= size; }

// Implementation Functions of Min Heap
int front(int H[]);
void push(int H[], int newNum);
void pop(int H[]);
void shiftUp(int H[], int idx);
void shiftDown(int H[], int idx);

void printKLargest(int arr[], int n, int k) // O(K + NlogK)
{
    // O(K): Create Min Heap of First K elements
    int *minHeap = (int *)malloc((k + 1) * sizeof(int));
    int i;
    for (i = 0; i < k; i++)
        minHeap[i + 1] = arr[i];

    size = k;
    for (i = size / 2; i >= 1; i--)
        shiftDown(minHeap, i);

    // O((N-K)logK): Heap contains k largest elements so far
    for (i = k; i < n; i++)
    {
        if (arr[i] > front(minHeap))
        {
            pop(minHeap);
            push(minHeap, arr[i]);
        }
    }

    /*
    // O(KlogK): (optional) Sort the heap in descending order
    int lastIdx, lastElem;
    while (size > 0)
    {
        lastIdx = size;
        lastElem = front(minHeap);
        pop(minHeap);
        minHeap[lastIdx] = lastElem;
    }
    */

    for (i = 1; i <= k; i++)
    {
        printf("%d ", minHeap[i]);
    }

    free(minHeap);
}

int main()
{   
    /*
    // HARD-CODED INPUT
    int arr[] = {89, 500, 22, -7, 81, -19, 34, 21, 222, 54, 68, -100, 88};
    printKLargest(arr, 13, 5);
    */

    // INTERACTIVE INPUT
    int n,k,i;
    printf("Enter number of elements in original array: ");
    scanf("%d",&n);

    int* arr = (int *)malloc(n*sizeof(int));
    printf("The original array: ");
    for(i=0;i<n;i++){
        scanf("%d",&arr[i]);
    }

    printf("Enter the value of k: ");
    scanf("%d",&k);

    if(k>n){
        printf("!! k can't be greater than %d\n",n);
        k = n;
    }

    printf("\n%d Largest Elements:\n",k);
    printKLargest(arr,n,k);
    printf("\n");
}

int front(int H[])
{
    return H[Root()];
}

void shiftUp(int H[], int idx)
{
    while (hasParent(idx) && (H[parent(idx)] > H[idx]))
    {
        swap(&H[parent(idx)], &H[idx]);
        idx = parent(idx);
    }
}

void shiftDown(int H[], int idx)
{
    while (isValidNode(leftChild(idx)))
    {
        int child = leftChild(idx);

        if (isValidNode(rightChild(idx)) && H[rightChild(idx)] < H[leftChild(idx)])
            child = rightChild(idx);

        if (H[idx] > H[child])
            swap(&H[idx], &H[child]);
        else
            break;

        idx = child;
    }
}

void push(int H[], int newNum)
{
    H[++size] = newNum;
    shiftUp(H, size);
}

void pop(int H[])
{
    H[Root()] = H[size--];
    shiftDown(H, Root());
}