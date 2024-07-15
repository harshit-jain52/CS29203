// 22CS10030 Harshit Jain
// Assignment 1 Question 1(ii)

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

    // Optimal TC: O(n)

    int ct=0,ans,el;

    for(i=0;i<n;i++){
        if(ct==0){
            el=fi[i];
            ct++;
            continue;
        }

        if(fi[i]==el)
            ct++;
        else
            ct--;
    }

    // it is assumed that most freq FI exists, otherwise we must check if count of 'el' in array is > n/2
    ans = el;
    
    printf("\nThe FI value present in most of the people: %d\n",ans);
}