// 22CS10030 Harshit Jain
// Assignment 3 Question 1

#include <stdio.h>
#include <limits.h>
#define MAXLEN 10000

typedef struct{
    int start;
    int end;
    int dur;
} prog;

int min(char x, char y){
    return (x<y) ? x : y;
}

int max(char x, char y){
    return (x>y) ? x : y;
}

int main(){
    int n,i,t;
    printf("\nNo. of programs: ");
    scanf("%d",&n);

    prog arr[MAXLEN];
    int minstamp=INT_MAX,maxstamp=INT_MIN;

    for ( i = 0; i < n; i++)
    {
        printf("%d. start, end, duration (seperated by space): ",i+1);
        scanf("%d %d %d",&arr[i].start,&arr[i].end,&arr[i].dur);
        minstamp = min(arr[i].start,minstamp);
        maxstamp = max(arr[i].end,maxstamp);
    }

    int allDone = 0;
    int marked[MAXLEN], ct[MAXLEN];

    for (t = minstamp; t <= maxstamp; t++)
    {
        marked[t]=0;
    }
    
    int mintime=0;

    while(!allDone){
        allDone = 1;
        for (t = minstamp; t <= maxstamp; t++)
        {
            ct[t]=0;
        }
        
        // count of programs that can run on particular time stamp
        for(i=0;i<n;i++){
            if(arr[i].dur>0)
            {   
                allDone=0;
                ct[arr[i].start]++;
                ct[arr[i].end+1]--;
            }
        }
        if(allDone) break;
        
        for (t = minstamp+1; t <= maxstamp; t++)
        {
            ct[t]+=ct[t-1];
        }
        // counts calculated using prefix sum

        int maxct=-1, timestamp=-1;

        for(t=minstamp;t<=maxstamp;t++){
            if(ct[t]>maxct && !marked[t]){
                maxct = ct[t];
                timestamp = t;
            }
        }

        marked[timestamp]=1;
        mintime++;

        for(i=0;i<n;i++){
            if(arr[i].dur>0)
            {   
                if(arr[i].start<=timestamp && arr[i].end>=timestamp){
                    arr[i].dur--;
                }
            }
        }
    }

    // TC: O(M*N); M = max end time - min start time, N = no. of programs
    
    printf("\nRequired minimum time: %d\n",mintime);
}