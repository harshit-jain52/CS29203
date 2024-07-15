// 22CS10030 Harshit Jain
// Lab Test 1 Question 2

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h> // use -lm flag while compiling
#include <float.h>
#define maxlen 100

typedef struct{
    int x;
    int y;
} city;

float calDist(int x1, int y1, int x2, int y2){
    return sqrtf((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
}

int main(){
    srand(time(NULL)); // seed the rand() function

    int n,i,j;
    printf("\nNo. of cities: ");
    scanf("%d",&n);

    city c[maxlen];

    printf("\nCity Coordinates:\n");
    for(i=0; i<n; i++){
        c[i].x = rand()%1000; // random value in range 0-999
        c[i].y = rand()%1000;

        printf("City %d: (%d,%d)\n",i,c[i].x,c[i].y);
    }

    float dist[maxlen][maxlen];

    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            if(i==j){
                dist[i][j] = 0;
                continue;
            }

            dist[i][j] = calDist(c[i].x,c[i].y,c[j].x,c[j].y);
        }
    }

    int visited[maxlen]={0};
    int currcity=0, nextcity;
    int path[maxlen], idx=0;
    float totaldist = 0, minDist;
    
    visited[0]=1;
    path[idx++]=0;

    while(idx<n){
        minDist = FLT_MAX;
        nextcity=-1;

        for(j=0;j<n;j++){
            if(visited[j]==1) continue;

            if(dist[currcity][j]<minDist){
                minDist = dist[currcity][j];
                nextcity=j;
            }
        }

        totaldist += minDist;
        path[idx++]=nextcity;
        visited[nextcity]=1;
        currcity=nextcity;
    }

    totaldist+=dist[currcity][0];
    path[idx]=0;

    printf("\nFinal Path: ");
    for(i=0;i<n;i++){
        printf("%d->",path[i]);
    }
    printf("%d",path[idx]);

    printf("\nCost: %.2f\n",totaldist);
}