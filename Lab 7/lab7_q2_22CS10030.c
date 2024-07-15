#include <stdio.h>
#include <stdlib.h>

// Boolean Implementation
#define bool int
#define true 1
#define false 0

// Graph Implementation
typedef struct node
{
    int data;
    struct node *next;
} node;

typedef struct graph
{
    int vnum;
    node **adjList;
    int *inDegree; // number of edges ending at a vertex
} graph;

node *createNode(int val);
graph *createGraph(int vertices);
void addDirectedEdge(graph *g, int src, int dest);

// Queue Implementation
#define MAXLEN 10000
#define datatype int

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

// Cycle Detection using Topological Sort
bool detectCycle(graph *g, int *topoSorted)
{   
    int n = g->vnum;
    int i, idx = 0;
    queue q = init();

    for (i = 0; i < n; i++)
        if (g->inDegree[i] == 0)
            q = enqueue(q, i);

    int cur_v, next_v;
    while (!isEmpty(q))
    {
        cur_v = front(q);
        q = dequeue(q);

        topoSorted[idx++] = cur_v;
        g->inDegree[cur_v] = -1; // Removing from graph

        node *traverser = g->adjList[cur_v];
        while (traverser != NULL)
        {
            next_v = traverser->data;

            g->inDegree[next_v]--;
            if (g->inDegree[next_v] == 0)
                q = enqueue(q, next_v);

            traverser = traverser->next;
        }
    }

    for(i = 0; i<n;i++){
        if(g->inDegree[i]>=0) return false;
    }
    return true;
}

int main()
{
    int n, m, x, y, i;
    printf("Enter no. of courses: ");
    scanf("%d",&n);
    
    graph *prereq = createGraph(n);
    
    printf("Enter no. of prerequisite conditions: ");
    scanf("%d",&m);

    printf("Enter %d conditions (course x has prereq course y) [x y]:\n",m);
    for (i = 0; i < m; i++)
    {
        scanf("%d %d", &x, &y);
        addDirectedEdge(prereq, y, x); // x has prereq y, so a directed edge from y to x
    }

    int *sequence = (int *)malloc(n * sizeof(int));

    bool isPossible = detectCycle(prereq, sequence);

    if(isPossible){
        printf("\nTrue. A possible sequence: \n");
        for (i = 0; i < n; i++)
        {
            printf("%d ", sequence[i]);
        }
        printf("\n");
    }
    else{
        printf("\nFalse\n");
    }
}

node *createNode(int val)
{
    node *vertex = (node *)malloc(sizeof(node));
    vertex->data = val;
    vertex->next = NULL;

    return vertex;
}

graph *createGraph(int vertices)
{
    graph *g = (graph *)malloc(sizeof(graph));

    g->vnum = vertices;
    g->adjList = (node **)malloc((g->vnum) * sizeof(node *));
    g->inDegree = (int *)malloc((g->vnum) * sizeof(int));

    int i;
    for (i = 0; i < g->vnum; i++)
    {
        g->adjList[i] = NULL;
        g->inDegree[i] = 0;
    }

    return g;
}

void addDirectedEdge(graph *g, int src, int dest)
{
    node *newNode = createNode(dest);
    newNode->next = g->adjList[src];
    g->adjList[src] = newNode;
    g->inDegree[dest]++;
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
