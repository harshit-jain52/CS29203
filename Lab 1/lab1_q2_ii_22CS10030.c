// 22CS10030 Harshit Jain
// Assignment 1 Question 2(ii)

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

    // Optimal 
    // TC: O(2*n) => O(n)
    // SC: O(1)

    long long totalSum=0,sumLeft=0;

    printf("\nStable indices in the list are: ");
    for(i=0;i<n;i++){
        totalSum+=fi[i];
    }

    for ( i = 0; i < n; i++)
    {
        if(totalSum-fi[i]-sumLeft==sumLeft){
            printf("%d ",i);
        }
        sumLeft+=fi[i];
    }

    printf("\n");
}