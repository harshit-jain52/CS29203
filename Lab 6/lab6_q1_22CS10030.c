// 22CS10030 Harshit Jain
// Assignment 6 Question 1

#include <stdio.h>
#include <stdlib.h>

void swap(int *x, int *y)
{
    int tmp = *x;
    *x = *y;
    *y = tmp;
}

int getMax(int H[]){ return H[0]; }
int getMin(int H[], int n){ return H[n-1]; }

int parentMin(int i, int n){ return n-((n-i)/2); }
int parentMax(int i) { return (i-1) / 2; }

int leftMin(int i, int n) { return n- (2*(n-i)); }
int rightMin(int i, int n) { return n- (2*(n-i) + 1); }
int leftMax(int i) { return 2 * i + 1; }
int rightMax(int i) { return 2 * i + 2; }

void shiftUpMin(int H[], int idx, int n);
void shiftUpMax(int H[], int idx);
void shiftDownMin(int H[], int idx, int minsz, int n);
void shiftDownMax(int H[], int idx, int maxsz);

void pushMin(int H[], int *minsz, int num, int n);
void deleteMin(int H[], int *minsz, int n);
void pushMax(int H[], int *maxsz, int num);
void deleteMax(int H[], int *maxsz);

void printHeap(int* medianHeap, int n);

void balanceHeaps(int H[], int *minsz, int *maxsz, int n, int *ct){
    if(*minsz > (*ct +1)/2){
        int tmp = getMin(H,n);
        deleteMin(H, minsz, n);
        pushMax(H,maxsz,tmp);
    }
    if(*maxsz > (*ct/2)){
        int tmp = getMax(H);
        deleteMax(H,maxsz);
        pushMin(H,minsz,tmp,n);
    }
}

int getMedian(int H[], int n, int ct){ 
    if(ct%2 ==0) return getMax(H);
    else return getMin(H,n);
}

void insert(int* medianHeap, int* minsz, int* maxsz, int num, int n, int *ct, int *med)
{
    if(*minsz ==0 || num > getMin(medianHeap,n)){
        pushMin(medianHeap,minsz,num,n);
    }
    else{
        pushMax(medianHeap,maxsz,num);
    }
    *ct = *ct +1;

    balanceHeaps(medianHeap,minsz,maxsz,n,ct);

    *med = getMedian(medianHeap,n,*ct);
}

void deleteMedian(int* medianHeap, int* minsz, int* maxsz, int n, int *ct, int *med){
    int num = *med;
    if(*ct%2==0){
        deleteMax(medianHeap,maxsz);
    }
    else{
        deleteMin(medianHeap,minsz,n);
    }
    *ct = *ct - 1;

    *med = getMedian(medianHeap,n,*ct);
}

void medHeapSort(int* medianHeap, int* minsz, int* maxsz, int n, int* ct, int *med){
    int prevmed,i;

    while(*ct>0)
    {
        prevmed = *med;
        i = *ct;

        deleteMedian(medianHeap,minsz,maxsz,n,ct,med);

        if(i%2==0){
            medianHeap[*maxsz] = prevmed;
        }
        else{
            medianHeap[n-*minsz-1] = prevmed;
        }
    }
}

int main()
{
    int n=20;

    /*
    // Interactive Input
    printf("\nEnter n: ");
    scanf("%d",&n); 
    */

    int* medianHeap = (int *)(malloc(n*sizeof(int)));
    int minsz =0, maxsz =0;
    // root of max heap is at index 0
    // root of minheap is at index n-1

    int ct = 0; // No. of elements being processed
    int med = -1;
    
    /*
    // Interactive Input
    int ch,x;
    while(ct<=n){
        printf("\nCurrent size = %d\n",ct);
        printf("1. Insert element\n2. Delete median\n3. Quit\nEnter choice: ");
        scanf("%d",&ch);

        if(ch==1){
            if(ct==n){
                printf("Filled to Capacity!\n");
            }
            else{
                printf("Enter number to insert: ");
                scanf("%d",&x);

                insert(medianHeap,&minsz,&maxsz,x,n,&ct,&med);
                printf("Insert(%d) Current Median: %d\n",x,med);
            }
        }
        else if(ch==2){
            if(ct==0){
                printf("Empty!\n");
            }
            else{
                x = med;
                deleteMedian(medianHeap,&minsz,&maxsz,n,&ct,&med);
                printf("DeleteMedian(%d) Current Median: %d\n",x,med);
            }
        }
        else if(ch==3) 
            break;
        else
            printf("Invalid Choice!\n");
    }
    */
    // HARD-CODED INPUT
    insert(medianHeap,&minsz,&maxsz,3064,n,&ct, &med);
    printf("Current Median: %d\n",med);
    insert(medianHeap,&minsz,&maxsz,545,n,&ct, &med);
    printf("Current Median: %d\n",med);
    insert(medianHeap,&minsz,&maxsz,2978,n,&ct, &med);
    printf("Current Median: %d\n",med);
    insert(medianHeap,&minsz,&maxsz,5176,n,&ct, &med);
    printf("Current Median: %d\n",med);
    insert(medianHeap,&minsz,&maxsz,7432,n,&ct, &med);
    printf("Current Median: %d\n",med);
    insert(medianHeap,&minsz,&maxsz,2687,n,&ct, &med);
    printf("Current Median: %d\n",med);
    insert(medianHeap,&minsz,&maxsz,3003,n,&ct, &med);
    printf("Current Median: %d\n",med);
    insert(medianHeap,&minsz,&maxsz,9903,n,&ct, &med);
    printf("Current Median: %d\n",med);
    deleteMedian(medianHeap,&minsz,&maxsz,n,&ct, &med);
    printf("Current Median: %d\n",med);
    insert(medianHeap,&minsz,&maxsz,7991,n,&ct, &med);
    printf("Current Median: %d\n",med);
    insert(medianHeap,&minsz,&maxsz,7963,n,&ct, &med);
    printf("Current Median: %d\n",med);
    insert(medianHeap,&minsz,&maxsz,6184,n,&ct, &med);
    printf("Current Median: %d\n",med);
    insert(medianHeap,&minsz,&maxsz,5426,n,&ct, &med);
    printf("Current Median: %d\n",med);
    insert(medianHeap,&minsz,&maxsz,9981,n,&ct, &med);
    printf("Current Median: %d\n",med);
    insert(medianHeap,&minsz,&maxsz,8838,n,&ct, &med);
    printf("Current Median: %d\n",med);
    insert(medianHeap,&minsz,&maxsz,8053,n,&ct, &med);
    printf("Current Median: %d\n",med);
    insert(medianHeap,&minsz,&maxsz,1069,n,&ct, &med);
    printf("Current Median: %d\n",med);
    insert(medianHeap,&minsz,&maxsz,2950,n,&ct, &med);
    printf("Current Median: %d\n",med);
    insert(medianHeap,&minsz,&maxsz,3625,n,&ct, &med);
    printf("Current Median: %d\n",med);
    insert(medianHeap,&minsz,&maxsz,9130,n,&ct, &med);
    printf("Current Median: %d\n",med);
    insert(medianHeap,&minsz,&maxsz,8458,n,&ct, &med);
    printf("Current Median: %d\n",med);
    insert(medianHeap,&minsz,&maxsz,9070,n,&ct, &med);
    printf("Current Median: %d\n",med);
    
    printHeap(medianHeap,n); // Full Heap
    medHeapSort(medianHeap,&minsz,&maxsz,n,&ct,&med);
    printHeap(medianHeap,n); // Sorted
}

void shiftUpMin(int H[], int idx, int n){
    while(idx!=(n-1) && H[parentMin(idx,n)]>H[idx]){
        swap(&H[idx],&H[parentMin(idx,n)]);
        idx = parentMin(idx,n);
    }
}

void shiftDownMin(int H[], int idx, int minsz, int n){
    int child = idx;
    
    while(1){
        if(n-leftMin(idx,n) <= minsz && H[leftMin(idx,n)] < H[child])
            child = leftMin(idx,n);
        
        if(n-rightMin(idx,n) <= minsz && H[rightMin(idx,n)] < H[child])
            child = rightMin(idx,n);
        
        if(child != idx){
            swap(&H[idx],&H[child]);
            idx = child;
        }
        else break;
    }
}

void pushMin(int H[], int *minsz, int num, int n){
    *minsz = *minsz + 1;
    H[n-*minsz] = num;

    shiftUpMin(H,n-*minsz,n);
}

void deleteMin(int H[], int *minsz, int n){
    H[n-1] = H[n-*minsz];
    H[n-*minsz] = 0; // empty
    *minsz = *minsz - 1;

    shiftDownMin(H, n-1,*minsz,n);
}

void shiftUpMax(int H[], int idx){
    while(idx!=0 && H[parentMax(idx)]<H[idx]){
        swap(&H[idx],&H[parentMax(idx)]);
        idx = parentMax(idx);
    }
}

void shiftDownMax(int H[], int idx, int maxsz){
    int child = idx;
    
    while(1){
        if(leftMax(idx) < maxsz && H[leftMax(idx)] > H[child])
            child = leftMax(idx);
        
        if(rightMax(idx) < maxsz && H[rightMax(idx)] > H[child])
            child = rightMax(idx);
        
        if(child != idx){
            swap(&H[idx],&H[child]);
            idx = child;
        }
        else break;
    }
}

void pushMax(int H[], int *maxsz, int num){
    *maxsz = *maxsz + 1;
    H[*maxsz-1] = num;

    shiftUpMax(H, *maxsz-1);
}

void deleteMax(int H[], int *maxsz){
    H[0] = H[*maxsz-1];
    H[*maxsz-1] = 0; //empty
    *maxsz = *maxsz - 1;
    shiftDownMax(H,0,*maxsz);
}

void printHeap(int* medianHeap, int n){
    int i;
    for(i=0;i<n;i++){
        printf("%d ",medianHeap[i]);
    }
    printf("\n");
}