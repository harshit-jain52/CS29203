// 22CS10030 Harshit Jain
// Assignment 1 Question 2(i)

#include<stdio.h>
#define maxlen 500000
int main(){
    printf("\nEnter number of FI to input: ");
    
    int n,i;
    scanf("%d",&n);

    int fi[maxlen];
    printf("\nEnter the FI list of the country (seperated by space): ");
    
    for(i=0;i<n;i++){
        scanf("%d",&fi[i]);
    }

    /*
    for(i = 0; i<n;i++){
        printf("%d ",arr[i]);
    }
    */

    // Brute Force TC: O(n^2)

    int stable[maxlen],idx=0;
    // this problem can be done without such an array,
    // by directly printing the indices (like in solution ii) instead of storing them
    
    int j;
    long long sumLeft,sumRight;

    for(i=0;i<n;i++){
        sumLeft=0,sumRight=0;

        for(j=0;j<=i-1;j++){
            sumLeft+=fi[j];
        }
        for(j=i+1;j<n;j++){
            sumRight+=fi[j];
        }

        if(sumLeft == sumRight){
            stable[idx]=i;
            idx++;
        }
    }

    printf("\nStable indices in the list are: ");
    for(i=0;i<idx;i++){
        printf("%d ",stable[i]);
    }
    printf("\n");
}