// 22CS10030 Harshit Jain
// Assignment 4 Question 2

#include <stdio.h>
#define maxlen 1000
int dp[maxlen+5];

typedef struct machine{
    int points;
    int skip;
} mach;

int max(int x, int y){
    return (x>y) ? x : y;
}

void memoize(int arr[], int val, int len){
    int i;
    for(i=0;i<=len;i++){
        arr[i]=val;
    }
}

int func(int idx, int n, mach m[]){
    if(idx>=n) return 0;
    if(dp[idx]!=-1) return dp[idx];

    int notplay = func(idx+1,n,m);
    int play = m[idx].points + func(idx+m[idx].skip+1,n,m);

    return dp[idx] = max(notplay,play);
}

int main(){
    int n,i;
    printf("\nNo. of machines: ");
    scanf("%d",&n);

    memoize(dp,-1,n); // assuming non-negative points

    mach m[100];
    for(i=0;i<n;i++){

        printf("%d. Points skipNumber (seperated by space): ",i+1);
        scanf("%d %d",&m[i].points,&m[i].skip);
    }

    printf("\nMaximum points: %d\n",func(0,n,m));
}