// 22CS10030 Harshit Jain
// Assignment 7 Question 1

#include <stdio.h>
#include <stdlib.h>

// Utility Function
int min(int x, int y){
    return (x<y)?x:y;
}
const int INF = 1e9;

// Graph Implementation
typedef struct node
{
    int data;
    int weight;
    struct node *next;
} node;

typedef struct graph
{
    int vnum;
    node **adjList;
} graph;

node *createNode(int val, int wt);
graph *createGraph(int numOfVertices);
void addDirectedEdge(graph *g, int src, int dest, int wt);

// Queue Implementation
#define MAXLEN 10000
typedef struct {
    int v;
    int depth;
    int cost;
} qnode;

#define datatype qnode

typedef struct
{
    datatype arr[MAXLEN];
    int front;
    int back;
} queue;

queue init();
int isEmpty(queue Q);
datatype front(queue Q);
queue enqueue(queue Q, datatype elem);
queue dequeue(queue Q);

// Breadth First Search
int BFS(graph *g, int src, int dest, int numEdges)
{   
    int mincost = INF;
    
    queue q = init();
    qnode tmp = {src,0,0};
    q = enqueue(q, tmp);

    int cur_v, cur_depth, cur_cost, child_v, child_cost;
    while (!isEmpty(q))
    {   
        tmp = front(q);
        q = dequeue(q);
        cur_v = tmp.v;
        cur_depth = tmp.depth;
        cur_cost = tmp.cost;
        
        if(cur_depth==numEdges){
            if(cur_v==dest){
                mincost = min(mincost,cur_cost);
            }
            continue;
        }
        
        node* traverser = g->adjList[cur_v];
        while (traverser != NULL)
        {
            child_v = traverser->data;
            child_cost = cur_cost + traverser->weight;

            tmp = (qnode){child_v,cur_depth+1,child_cost};
            q = enqueue(q, tmp);

            traverser = traverser->next;
        }
    }

    return mincost;
}

int main()
{
    int n, m, x, y, w, i, src, dest, num;
    printf("Enter no. of vertices n [vertices are 0 to (n-1)]: ");
    scanf("%d",&n);

    graph* g = createGraph(n);

    printf("Enter no. of edges in the graph: ");
    scanf("%d",&m);

    printf("Enter %d edges [from-vertex to-vertex weight-of-edge]:\n",m);

    for ( i = 0; i < m; i++)
    {
        scanf("%d%d%d",&x,&y,&w);
        addDirectedEdge(g,x,y,w);
    }
    
    // for(i =0; i<n; i++){
    //     printf("%d-> ",i);
    //     node* trav = g->adjList[i];
    //     while(trav!=NULL){
    //         printf("%d,%d\t",trav->data,trav->weight);
    //         trav = trav->next;
    //     }
    //     printf("\n");
    // }

    printf("Enter source-vertex destination-vertex number-of-edges: ");
    scanf("%d %d %d", &src, &dest, &num);

    int req_cost = BFS(g,src,dest,num);
    if(req_cost == INF){
        printf("\nNot Possible\n");
    }
    else{
        printf("\nMinimum cost from %d to %d via %d edges: %d\n",src,dest,num,req_cost);
    }
}

node *createNode(int val, int wt)
{
    node *vertex = (node *)malloc(sizeof(node));
    vertex->data = val;
    vertex->weight = wt;
    vertex->next = NULL;

    return vertex;
}

graph *createGraph(int numOfVertices)
{
    graph *g = (graph *)malloc(sizeof(graph));

    g->vnum = numOfVertices;
    g->adjList = (node **)malloc((g->vnum) * sizeof(node *));

    int i;
    for (i = 0; i < g->vnum; i++)
    {
        g->adjList[i] = NULL;
    }

    return g;
}

void addDirectedEdge(graph *g, int src, int dest, int wt)
{
    node *newNode = createNode(dest,wt);
    newNode->next = g->adjList[src];
    g->adjList[src] = newNode;
}

queue init()
{
    queue Q;
    Q.front = 0;
    Q.back = MAXLEN - 1;
    return Q;
}

int isEmpty(queue Q)
{
    return (Q.front == (Q.back + 1) % MAXLEN);
}

datatype front(queue Q)
{
    return Q.arr[Q.front];
}

queue enqueue(queue Q, datatype elem)
{
    Q.back = (++Q.back) % MAXLEN;
    Q.arr[Q.back] = elem;
    return Q;
}

queue dequeue(queue Q)
{
    Q.front = (++Q.front) % MAXLEN;
    return Q;
}
