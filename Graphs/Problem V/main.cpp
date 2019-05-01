#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

#define MAX_V 500
#define MAX_NUMBER 99999

int n_vertex;
vector<vector<int> > adj_matrix;
vector<vector<int> > dist;


vector<vector<int> > init_graph(int n){
  vector<vector<int> > m(n,vector<int>(n,-1));
  return m;
}


void floydWarshall (int source, int target) 
{ 
    /* dist[][] will be the output matrix that will finally have the shortest  
      distances between every pair of vertices */
    int  i, j, k;

    
   if(source>target){
       swap(source,target);
       
   }
   dist= init_graph((target-source)+1); 
    /* Initialize the solution matrix same as input graph matrix. Or  
       we can say the initial values of shortest distances are based 
       on shortest paths considering no intermediate vertex. */
    for (i = source; i <= target; i++) 
        for (j = source; j <= target; j++){
            if(adj_matrix[i][j]!=-1){
                dist[i-source][j-source] = adj_matrix[i][j]; 
                dist[j-source][i-source] = adj_matrix[j][i]; 
            }
            else
            {
                dist[i-source][j-source]=MAX_NUMBER;
                dist[j-source][i-source]=MAX_NUMBER;
            }
            
        }
    /* Add all vertices one by one to the set of intermediate vertices. 
      ---> Before start of an iteration, we have shortest distances between all 
      pairs of vertices such that the shortest distances consider only the 
      vertices in set {0, 1, 2, .. k-1} as intermediate vertices. 
      ----> After the end of an iteration, vertex no. k is added to the set of 
      intermediate vertices and the set becomes {0, 1, 2, .. k} */

    for (k = source; k <= target; k++) 
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
                if (dist[i-source][k-source] + dist[k-source][j-source] < dist[i-source][j-source]) 
                    dist[i-source][j-source] = dist[i-source][k-source] + dist[k-source][j-source]; 
            } 
        } 
    } 
    /*cout<<"Source : "<<source+1<<" Target : "<<target+1<<endl;
    for(int i=0;i<=target-source;i++){
        for(int j=0;j<=target-source;j++){
            cout<<dist[i][j]<<" ";
        }
        cout<<endl;
    }*/
  
    // Print the shortest distance matrix 
    cout<<dist[source-source][target-source]<<endl;
} 

int main(){
    cin>>n_vertex;

    adj_matrix = init_graph(n_vertex);

    for(int i=0;i<n_vertex;i++){
        for(int j=0;j<n_vertex;j++){
            cin>>adj_matrix[i][j];
        }
    }
    for(int i=1;i<n_vertex;i++){
        int source, target;
        cin>>source>>target;
        floydWarshall(source-1,target-1);
    }
    return 0;
}