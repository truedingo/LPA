
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

#define MAX_ARRAY 100

int n_functions;

int recursive_calls [MAX_ARRAY][MAX_ARRAY];
int G[MAX_ARRAY][MAX_ARRAY];
bool visited[MAX_ARRAY];

// This function returns true if  
// graph G[V][V] is Bipartite, else false 
void BFS(int src) 
{ 
    visited[src]=true;
    // Create a queue (FIFO) of vertex numbers a 
    // nd enqueue source vertex for BFS traversal 
    queue <int> q; 
    q.push(src); 
  
    // Run while there are vertices in queue (Similar to BFS) 
    while (!q.empty()) 
    { 
        // Dequeue a vertex from queue ( Refer http://goo.gl/35oz8 ) 
        int u = q.front(); 
        cout<<u<<endl;
        q.pop(); 
  
    
        // Find all non-colored adjacent vertices 
        for (int v = 0; v < n_functions; ++v) 
        { 
            // An edge from u to v exists and 
            // destination v is not colored 
            if (!visited[v]) 
            { 
                // Assign alternate color to this 
                // adjacent v of u 
                visited[v]=true;
                q.push(v); 
            } 
  
        
        } 
        
    } 
  
    // If we reach here, then all adjacent vertices can 
    // be colored with alternate color 

   
} 





int main(){

    cin >> n_functions;

    for(int i=0;i<n_functions;i++){
        for(int j=0;j<n_functions;j++){
            G[i][j]=0;
        }
    }
    
    for(int i=0;i< n_functions ;i++){
        int n_function_aux = -1;
        cin >> n_function_aux;
        for (int j=0;j<n_function_aux;j++){
            int id;
            cin>>id;
            G[i][id]=1;
        }
    }

    for(int i=0;i<n_functions;i++){
        for(int j=0;j<n_functions;j++){
            cout<<G[i][j]<<" ";
        }
        cout<<endl;
    }

    BFS(0);


 
}