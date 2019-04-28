#include <iostream>
#include <vector>

using namespace std;

#define MAX_V 500
#define MAX_NUMBER 10000000

int n_vertex;
int source=0, target=0;
int adj_matrix[MAX_V][MAX_V];
int dist[MAX_V][MAX_V];




void floydWarshall (int source, int target) 
{ 
    /* dist[][] will be the output matrix that will finally have the shortest  
      distances between every pair of vertices */
    int  i, j, k; 
     if(source>target){
        int temp = source;
        source = target;
        target = temp;
    }
    /* Initialize the solution matrix same as input graph matrix. Or  
       we can say the initial values of shortest distances are based 
       on shortest paths considering no intermediate vertex. */
    for (i = 0; i <= n_vertex; i++) 
        for (j = 0; j <= n_vertex; j++){
            if(adj_matrix[i][j]!=-1){
                dist[i][j] = adj_matrix[i][j]; 
                dist[j][i] = adj_matrix[j][i]; 
            }
            else
            {
                dist[i][j]=MAX_NUMBER;
                dist[j][i]=MAX_NUMBER;
            }
            
        }
    /* Add all vertices one by one to the set of intermediate vertices. 
      ---> Before start of an iteration, we have shortest distances between all 
      pairs of vertices such that the shortest distances consider only the 
      vertices in set {0, 1, 2, .. k-1} as intermediate vertices. 
      ----> After the end of an iteration, vertex no. k is added to the set of 
      intermediate vertices and the set becomes {0, 1, 2, .. k} */

    for (k = source; k < target+1; k++) 
    { 
        // Pick all vertices as source one by one 
        for (i = source; i <= target; i++) 
        { 
            // Pick all vertices as destination for the 
            // above picked source 
            for (j = source; j <= target; j++) 
            { 
                // If vertex k is on the shortest path from 
                // i to j, then update the value of dist[i][j] 
                if (dist[i][k] + dist[k][j] < dist[i][j]) 
                    dist[i][j] = dist[i][k] + dist[k][j]; 
            } 
        } 
    } 
  
    // Print the shortest distance matrix 
    cout<<dist[source][target]<<endl;
} 

int main(){
    cin>>n_vertex;
    for(int i=0;i<n_vertex;i++){
        for(int j=0;j<n_vertex;j++){
            cin>>adj_matrix[i][j];
        }
    }
    for(int i=1;i<n_vertex;i++){
       
        cin>>source>>target;
        floydWarshall(source-1,target-1);
    }
    return 0;
}