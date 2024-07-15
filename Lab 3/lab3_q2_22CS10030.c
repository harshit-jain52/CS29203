// 22CS10030 Harshit Jain
// Assignment 3 Question 2

#include <stdio.h>
#define MAXLEN 10000
#define datatype char

// stack definition starts
typedef struct
{
    datatype arr[MAXLEN];
    int top;
} stack;

stack init()
{
    stack S;

    S.top = -1;
    return S;
}

int isEmpty(stack S)
{
    return (S.top == -1);
}

int isFull(stack S)
{
    return (S.top == MAXLEN - 1);
}

datatype top(stack S)
{
    if (isEmpty(S))
    {
        printf("\ntop: Empty Stack\n");
        return 0;
    }

    return S.arr[S.top];
}

stack push(stack S, datatype elem)
{
    if (isFull(S))
    {
        printf("\npush: Full Stack\n");
        return S;
    }

    S.arr[++S.top] = elem;
    return S;
}

stack pop(stack S)
{
    if (isEmpty(S))
    {
        printf("\npop: Empty Stack\n");
        return S;
    }

    --S.top;
    return S;
}
// stack definition ends

char min(char x, char y){
    return (x<y) ? x : y;
}

int main(){
    int n,i;
    printf("\nLength of input string: ");
    scanf("%d",&n);

    char input[MAXLEN];
    printf("\nInput String: ");
    scanf("%s",input);

    char minFromRight[MAXLEN]; // store what is the smallest character to the right of an index
    minFromRight[n-1]=input[n-1];

    for(i=n-2;i>=0;i--){
        minFromRight[i]=min(minFromRight[i+1],input[i]);
    }

    // for(i=0;i<n;i++){
    //     printf("%c ",minFromRight[i]);
    // }

    int startIdx=0; // index from which we should start checking to the right for smallest character
    stack work = init();
    char output[MAXLEN];
    int idx=0; // current index of output string

    while(startIdx<n){
        while(!isEmpty(work) && top(work)<=minFromRight[startIdx]) {
            // inserting left elements which are <= smallest element at right
            output[idx] = top(work);
            work = pop(work);
            idx++;
        }

        int start = startIdx;
        for(i=start;i<n;i++){
            // traversing to right to get current smallest character
            if(input[i]==minFromRight[start]){
                output[idx]=input[i];
                idx++;
                startIdx=i+1;
            }
            else{
                if(minFromRight[i]!=minFromRight[start]) break;

                work = push(work,input[i]);
            }
        }
    }
    
    while(!isEmpty(work)){
        output[idx]=top(work);
        idx++;
        work = pop(work);
    }

    output[idx]='\0';

    printf("\nOutput String: %s\n",output);
}