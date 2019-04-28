// C++ program to find out whether a 
// given graph is Bipartite or not 
#include <iostream> 
#include <queue> 
#define MAX_VERTEX 100
using namespace std; 


int n_vertex;
int G[MAX_VERTEX][MAX_VERTEX];
bool visited[MAX_VERTEX];

// This function returns true if  

int BFS(int src) 
{ 
    int solution=0;
    for(int i=0;i<n_vertex;i++){
        visited[i]=false;
    }
  
    // Create a queue (FIFO) of vertex numbers a 
    // nd enqueue source vertex for BFS traversal 
    queue <int> q; 
    visited[src] = true;
    q.push(src); 
  
    // Run while there are vertices in queue (Similar to BFS) 
    while (!q.empty()) 
    { 
        // Dequeue a vertex from queue ( Refer http://goo.gl/35oz8 ) 
        int t = q.front(); 
        
        q.pop(); 
  
       
        for (t = 0; t < n_vertex; t++) 
        { 
            for(int u=0;u<n_vertex;u++){
                
                if(G[t][u]==1){
                    cout<<"T: "<<t<<" U: "<<u<<endl;
                    if (!visited[u]) 
                    { 
                        visited[u] = true;
                        q.push(u); 
                        if(u==src){
                            solution++;
                           
                        }
                    }
                }
            }
  
           
        } 
    } 
  
    return solution;
    
} 
  


// Driver program to test above function 
int main() 
{ 
    cin >> n_vertex;

	
	for (int i=0;i<n_vertex;i++){
        for (int j=0;j<n_vertex;j++){
            cin>>G[i][j];
        }
    }

    cout<<BFS(0)<<endl;
	return 0; 
} 

