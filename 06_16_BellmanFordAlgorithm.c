#include <stdio.h>
#include <limits.h>

#define V 5   // number of vertices
#define E 8   // number of edges

// Bellman-Ford Algorithm
void bellmanFord(int edges[E][3], int src) {
    int dist[V];
    for (int i = 0; i < V; i++) dist[i] = INT_MAX;
    dist[src] = 0;

    // Relax all edges |V|-1 times
    for (int i = 1; i < V; i++) {
        for (int j = 0; j < E; j++) {
            int u = edges[j][0];
            int v = edges[j][1];
            int w = edges[j][2];
            if (dist[u] != INT_MAX && dist[u] + w < dist[v])
                dist[v] = dist[u] + w;
        }
    }

    // Check for negative-weight cycle
    for (int j = 0; j < E; j++) {
        int u = edges[j][0];
        int v = edges[j][1];
        int w = edges[j][2];
        if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
            printf("Graph contains negative weight cycle\n");
            return;
        }
    }

    // Print results
    for (int i = 0; i < V; i++)
        printf("Vertex %d \t Distance = %d\n", i, dist[i]);
}

int main() {
    int edges[E][3] = {
        {0,1,-1}, {0,2,4}, {1,2,3}, {1,3,2},
        {1,4,2}, {3,2,5}, {3,1,1}, {4,3,-3}
    };

    bellmanFord(edges, 0);
    return 0;
}
