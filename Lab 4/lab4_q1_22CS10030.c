// 22CS10030 Harshit Jain
// Assignment 4 Question 1

#include <stdio.h>
#include <string.h>
#define maxlen 1000

int max(int x, int y){
    return (x>y) ? x : y;
}

int main(){
    char x[maxlen], y[maxlen];
    int i,j;

    int numx,numy;
    printf("Enter length of string X: ");
    scanf("%d",&numx);
    
    if(numx>0){
        printf("string X: ");
        scanf("%s",x);
    }

    printf("Enter length of string Y: ");
    scanf("%d",&numy);

    if(numy>0){
        printf("string Y: ");
        scanf("%s",y);
    }
    
    // Handling Blank Strings first
    if(numx==0 && numy==0){
        printf("\nBoth strings are empty\n");
        return 0;
    }

    if(numx==0){
        j=0;

        printf("\n");
        while(j<numy){
            printf("+%c ",y[j]);
            j++;
        }
        printf("\n");

        return 0;
    }

    if(numy==0){
        i=0;

        printf("\n");
        while(i<numx){
            printf("-%c ",x[i]);
            i++;
        }
        printf("\n");

        return 0;
    }

    int dp[maxlen+2][maxlen+2];

    for(i=0;i<=numx;i++){
        dp[i][0]=0;
    }
    for(j=0;j<=numy;j++){
        dp[0][j]=0;
    }

    for(i=1;i<=numx;i++){
        for(j=1;j<=numy;j++){
            if(x[i-1]==y[j-1]){
                dp[i][j] = 1 + dp[i-1][j-1];
            }
            else{
                dp[i][j] = max(dp[i-1][j],dp[i][j-1]);
            }
        }
    }

    // printf("\nlength of LCS: %d\n",dp[numx][numy]);

    char ans[3*maxlen];
    int idx=0; //position in ans

    i=numx,j=numy;
    while(i>0 && j >0){
        if(x[i-1]==y[j-1]){
            ans[idx++]=x[i-1];
            i--;
            j--;
        }
        else{
            if(dp[i-1][j]>dp[i][j-1]){
                ans[idx++]=x[i-1];
                ans[idx++]='-';
                i--;
            }
            else{
                ans[idx++]=y[j-1];
                ans[idx++]='+';
                j--;
            }
        }
        
        ans[idx++]=' ';
    }

    while(i>0){
        ans[idx++]=x[i-1];
        ans[idx++]='-';
        i--;

        ans[idx++]=' ';
    }

    while(j>0){
        ans[idx++]=y[j-1];
        ans[idx++]='+';
        j--;

        ans[idx++]=' ';
    }

    ans[idx]='\0';
    // printf("\n%s\n",ans);

    printf("\n");
    for(i=idx-1;i>=0;i--){
        printf("%c",ans[i]);
    }
    printf("\n");

    return 0;
}