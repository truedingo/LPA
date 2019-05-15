#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

int V;
int edges;

#define M 751
int Graph[M][M] = {{0}};

void clean_Graph()
{
    int i, ii;
    for (i = 1; i < M; i++)
    {
        for (ii = 1; ii < M; ii++)
        {
            Graph[i][ii] = 0;
        }
    }
}


double weight(int * x_c, int * y_c, int n1, int n2)
{
    return (double) sqrt( (double) fabs(x_c[n1] - x_c[n2]) * (double) fabs(x_c[n1] - x_c[n2]) + (double) fabs(y_c[n1] - y_c[n2]) * (double)fabs(y_c[n1] - y_c[n2]));
}

struct subset 
{ 
    int parent; 
    int rank; 
};

struct edge
{
    int e, d;
    double weight;
};
   
int find(struct subset subsets[], int i) 
{
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
  
    return subsets[i].parent; 
}


void Union(struct subset subsets[], int x, int y) 
{ 
    int xroot = find(subsets, x); 
    int yroot = find(subsets, y);
  

    if (subsets[xroot].rank < subsets[yroot].rank) 
        subsets[xroot].parent = yroot; 
    else if (subsets[xroot].rank > subsets[yroot].rank) 
        subsets[yroot].parent = xroot; 

    else
    { 
        subsets[yroot].parent = xroot; 
        subsets[xroot].rank++; 
    } 
}

int myComp(const void* a, const void* b) 
{ 
    struct edge* a1 = (struct edge*)a; 
    struct edge* b1 = (struct edge*)b;
    
    return a1->weight > b1->weight; 
} 


void KruskalMST(struct edge* E, struct subset * subsets, int num_missing_edges)
{ 
     
    
    int i = 0;
    // edges é o nr de edges
    double c = 0;

    qsort(E, num_missing_edges, sizeof(struct edge), myComp); 

    
    while (i < num_missing_edges)
    {
        
        struct edge next_edge = E[i++];

        // cout << next_edge.e << " " << next_edge.d << " " << next_edge.weight << endl;

        if (Graph[next_edge.e][next_edge.d] == 0 && Graph[next_edge.d][next_edge.e] == 0)
        {
            // cout << "Escolhi " << next_edge.e << " " << next_edge.d << " " << next_edge.weight << endl;
            int x = find(subsets, next_edge.e);
            int y = find(subsets, next_edge.d);

            if (x != y)
            {
                Union(subsets, x, y);
                Graph[next_edge.e][next_edge.d] = 1, Graph[next_edge.d][next_edge.e] = 1;
                c += next_edge.weight;
            }
        }

    }

    printf("%.2lf\n",c); 
    return; 
} 


int main()
{

    int n;
    int e, d;
    
    while(cin >> n)
    {
        
        V = n;
        int x_coord[n], y_coord[n];
        clean_Graph();

        for (int i = 1; i <= n; ++i)
        {
            cin >> x_coord[i], cin >> y_coord[i];
        }

        
        struct subset *subsets = (struct subset*) malloc(1010 * sizeof(struct subset) );
        for (int v = 1; v <= V; ++v)
        {
            subsets[v].parent = v; 
            subsets[v].rank = 0;
        }

        cin >> edges;
        struct edge *E = (struct edge*) malloc( 1010* 1010* sizeof(struct edge));
        int c = 0;


        for(int i=1;i<=n;i++)
		    for(int j=i+1;j<=n;j++)
			{
                E[c].e = i;
                E[c].d = j;
                E[c].weight = weight(x_coord, y_coord, i, j);
                c++;
            }
    
        for (int i = 0; i < edges; ++i)
        {
            cin >> e, cin >> d;

            Graph[e][d] = 1;
            Graph[d][e] = 1;
            
            // Union the inputed edges
            int x = find(subsets, e), y = find(subsets, d);
            
            if (x != y)
            {
                //cout<<"Junta: "<<x<<" com "<<y<<endl;
                Union(subsets, x, y);
            }
        }
        KruskalMST(E, subsets, c); 
    }


    return 0;
}
