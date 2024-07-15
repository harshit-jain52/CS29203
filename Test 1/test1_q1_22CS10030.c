// 22CS10030 Harshit Jain
// Lab Test 1 Question 1

#include <stdio.h>
#define maxlen 1000

int max(int x, int y){
    return (x>y) ? x : y;
}

int canDistribute(int x, int n, int prizes[], int p){
    int i,num = 0;
    for(i=0;i<p;i++){
        num += (prizes[i]/x + (prizes[i]%x!=0)); // ceil of prizes[i]/x
    }

    return (num<=n);
}

int main()
{
    int n,p,i,m=0,sum=0;
    int prizes[maxlen];

    printf("\nNo. of students: ");
    scanf("%d",&n);

    printf("\nNo. of types of prizes: ");
    scanf("%d",&p);

    printf("\nEnter no. of prizes of:\n");
    
    for(i=0;i<p;i++){
        printf("Type %d: ",i+1);
        scanf("%d",&prizes[i]);
        m = max(m,prizes[i]);
        sum += prizes[i];
    }

    if(p>n || sum<n){
        printf("\nDistribution not possible");
        if(p>n) printf("\nNo. of types of prizes > No. of students\n");
        else printf("\nSome students would get zero prizes\n");
        return 0;
    }

    // Binary Search on Answer
    int lo=1,hi=m,mid;
    while(hi-lo>1)
    {
        mid = (lo+hi)/2;

        if(canDistribute(mid,n,prizes,p)) hi=mid;
        else lo=mid+1;
    }

    int ans=-1;
    if(canDistribute(lo,n,prizes,p)) ans = lo;
    else if(canDistribute(hi,n,prizes,p)) ans = hi;

    printf("\nMax number of prizes given to any student: %d\n",ans);
}