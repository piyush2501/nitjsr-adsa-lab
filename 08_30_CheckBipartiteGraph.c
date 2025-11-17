#include <stdio.h>

#define MAXN 1000
#define QUEUE_SIZE 10000

int n, e;
int adj[MAXN][MAXN];
int color[MAXN];

int queue[QUEUE_SIZE];
int front = 0, rear = 0;

void enqueue(int v)
{
    queue[rear++] = v;
}

int dequeue()
{
    return queue[front++];
}

int is_bipartite()
{
    for (int i = 0; i < n; i++)
        color[i] = 0;

    for (int start = 0; start < n; start++)
    {
        if (color[start] != 0)
            continue;

        color[start] = 1;
        front = rear = 0;
        enqueue(start);

        while (front < rear)
        {
            int u = dequeue();
            for (int v = 0; v < n; v++)
            {
                if (adj[u][v])
                {
                    if (color[v] == 0)
                    {
                        color[v] = -color[u];
                        enqueue(v);
                    }
                    else if (color[v] == color[u])
                    {
                        return 0;
                    }
                }
            }
        }
    }
    return 1;
}

int main()
{
    printf("Enter number of vertices (n) and edges (e): ");
    scanf("%d %d", &n, &e);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            adj[i][j] = 0;

    printf("Enter edges (u v) 0-based:\n");
    for (int i = 0; i < e; i++)
    {
        int u, v;
        scanf("%d %d", &u, &v);
        adj[u][v] = adj[v][u] = 1;
    }

    if (is_bipartite())
        printf("Graph is bipartite\n");
    else
        printf("Graph is NOT bipartite\n");

    return 0;
}
