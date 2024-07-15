// 22CS10030 Harshit Jain
// Lab Test 1 Question 3

#include <stdio.h>
#define maxlen 10

float max(float x, float y){
    return (x>y) ? x : y;
}

// Initialization for Memoisation
void fillDP(float dp[][maxlen+1],int n, float val){
    int i,j;
    for(i=0;i<=n;i++){
        for(j=0;j<=n;j++){
            dp[i][j]=val;
        }
    }
}

float evaluate(int l, int r, char op[], float a[], float dp[][maxlen+1]){
    if(l==r) return a[l];

    if(dp[l][r]!=0) return dp[l][r];

    float ans = 0;
    int i;

    for(i=l;i<r;i++){
        if(op[i]=='*') ans = max(ans, evaluate(l,i,op,a,dp)*evaluate(i+1,r,op,a,dp));
        else ans = max(ans, evaluate(l,i,op,a,dp)+evaluate(i+1,r,op,a,dp));
    }

    return dp[l][r] = ans;
}

int main(){
    int n,i;
    float a[maxlen];
    char op[maxlen];

    float dp[maxlen+1][maxlen+1];

    printf("\nNo. of positive numbers (max value %d): ",maxlen);
    scanf("%d",&n);

    printf("\nEnter %d numbers from left to right:\n",n);
    for(i=0;i<n;i++)
    {
        scanf("%f",&a[i]);
    }

    printf("\nEnter %d operators from left to right (+,*):\n",n-1);
    for(i=0;i<n-1;i++){
        scanf(" %c",&op[i]); // " %c" instead of "%c" to take care of whitespace while reading input
    }

    fillDP(dp,n,0);
    float maxval = evaluate(0,n-1,op,a,dp);

    printf("\nMax value of expression is: %f\n",maxval);
}