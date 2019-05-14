#include <iostream>
#include <string>
#include <sstream>
#include <stdio.h>
using namespace std;
#define M 801
#define NIL -1
int graph[M][M] = {{0}};
int V;





void clean_Graph()
{
    int i, j;
    for (i = 1; i < M; i++)
    {
        for (j = 1; j < M; j++)
        {
            graph[i][j] = 0;
        }
    }
}

void Articulation_Points(int u, bool visited[], int disc[],
                                      int low[], int parent[], bool ap[])
{

    static int time = 0;

    int children = 0;

    visited[u] = true;

    disc[u] = low[u] = ++time;

    int i;
    for (i = 1; i < V; ++i)
    {
        int v = i;
        if(graph[u][i] != 0) {

            if (!visited[v])
            {
                children++;
                parent[v] = u;

                Articulation_Points(v, visited, disc, low, parent, ap);

                low[u]  = min(low[u], low[v]);

                if (parent[u] == NIL && children > 1) {
                    ap[u] = true;

                }

                if (parent[u] != NIL && low[v] >= disc[u]) {
                    ap[u] = true;
                }
            }
            else if (v != parent[u])
                low[u]  = min(low[u], disc[v]);
        }
    }
}

void G_Articulation_Points()
{

    bool *visited = new bool[V];
    int *disc = new int[V];
    int *low = new int[V];
    int *parent = new int[V];
    bool *ap = new bool[V];

    for (int i = 1; i < V; i++)
    {
        parent[i] = NIL;
        visited[i] = false;
        ap[i] = false;
    }

    for (int i = 1; i < V; i++)
        if (visited[i] == false)
            Articulation_Points(i, visited, disc, low, parent, ap);

    int c, max = -1;

    for (int i = 1; i < V; i++) {
        c = 0;
        if (ap[i] == true)
        {
            for (int j = 1; j < V; j++)
            {
                c += graph[i][j];
            }
            if (c > max) max = c;
        }
    }

    if (max == -1)
    {
        printf("Strong network\n");
    }
    else
    {
        printf("%d\n", max);
    }

}

int main()
{
    int n_crossigns, i, n_cons, n, id;
    while(cin >> n_crossigns)
    {
        clean_Graph();
        V = n_crossigns + 1;
        for (i = 1; i <= n_crossigns; ++i)
        {
            cin >> n_cons;
            for (n = 0; n < n_cons; ++n)
            {
                cin >> id;
                graph[i][id] = 1;
                graph[id][i] = 1;
            }
        }
        G_Articulation_Points();
    }


    return 0;
}
