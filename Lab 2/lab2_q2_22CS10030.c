// 22CS10030 Harshit Jain
// Assignment 2 Question 2

#include <stdio.h>
#include <float.h>
#define maxlen 100000

typedef struct{
    float x;
    float y;
    int idx;
} point;

int numDominant[maxlen];

// user-defined functions written below main
void mergeSortbyY(point arr[], int l, int r);
void mergebyY(point arr[], int l, int m, int r);
void divide(point arr[],int l, int r);
void conquer(point arr[], int l, int m, int r);

int main()
{
    int n,i;
    point org[maxlen];

    printf("\nNo. of points: ");
    scanf("%d",&n);

    printf("\nOriginal Points:\n");
    for(i=0;i<n;i++){
        printf("\nPoint %d\n",i+1);
        printf("X,Y (seperated by space): ");
        scanf("%f %f",&org[i].x,&org[i].y);
        org[i].idx=i;
        numDominant[i]=0;
    }

    // NOTE: This program has been written under assumption that all X's are diff as well as all Y's are diff
    
    mergeSortbyY(org,0,n-1); // sort by Y

    /*
    for(i=0;i<n;i++){
        printf("\n%f %f %d",org[i].x,org[i].y,org[i].idx);
    }
    */

    divide(org,0,n-1); // count dominance while dividing into HIGH & LOW and sorting them by X
    
    // TC: O(2NlogN) ==> O(NlogN)

    printf("\nDominance: ");
    for(i=0;i<n;i++){
        printf("%d ",numDominant[i]);
    }
}

void mergeSortbyY(point arr[], int l, int r)
{
    if (l >= r)
        return;

    int mid = (l + r) / 2;

    mergeSortbyY(arr, l, mid);
    mergeSortbyY(arr, mid + 1, r);

    mergebyY(arr, l, mid, r);
}

void mergebyY(point arr[], int l, int m, int r)
{
    int n1 = m - l + 1, n2 = r - m;
    int i, j, k;

    point left[maxlen];
    point right[maxlen];

    for (i = 0; i < n1; i++)
        left[i] = arr[l + i];

    for (j = 0; j < n2; j++)
        right[j] = arr[m + 1 + j];

    // safety measure
    left[n1].x = right[n2].x = left[n1].y = right[n2].y = FLT_MAX;
    left[n1].idx = right[n2].idx=-1;

    i = 0;
    j = 0;
    k = l;

    while (k<=r)
    {
        if (left[i].y < right[j].y)
        {
            arr[k] = left[i];
            i++;
        }
        else
        {   
            arr[k] = right[j];
            j++;
        }
        k++;
    }
}

void divide(point arr[],int l, int r)
{
    if (l >= r)
        return;

    int mid = (l + r) / 2;

    divide(arr, l, mid);
    divide(arr, mid + 1, r);

    conquer(arr, l, mid, r);
}

void conquer(point arr[], int l, int m, int r)
{
    int n1 = m - l + 1, n2 = r - m;
    int i, j, k;

    point low[maxlen];
    point high[maxlen];
    // every Y of low will be less than every Y of high

    for (i = 0; i < n1; i++)
        low[i] = arr[l + i];

    for (j = 0; j < n2; j++)
        high[j] = arr[m + 1 + j];
    
    // safety measure
    low[n1].x = high[n2].x = low[n1].y = high[n2].y = FLT_MAX;
    low[n1].idx = high[n2].idx=-1;

    i = 0;
    j = 0;
    k = l;

    while (k<=r)
    {
        if(low[i].x > high[j].x)
        {   
            numDominant[high[j].idx]+=i; // no need to check for Y as it's already taken care of
            arr[k]=high[j];
            j++;
        }
        else{
            arr[k]=low[i];
            i++;
        }
        k++;
    }
}