// 22CS10030 Harshit Jain
// Assignment 1 Question 1(i)

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

    int ct,ans,el,j;

    for(i=0;i<n;i++){
        ct=0;
        el=fi[i];
        for(j=0;j<n;j++){
            if(fi[j]==el){
                ct++;
            }
        }
        if(ct>n/2){
            ans = el;
            break;
        }
    }

    // it is assumed that most freq FI exists, otherwise 'ans' could be a garbage value
    
    printf("\nThe FI value present in most of the people: %d\n",ans);
}