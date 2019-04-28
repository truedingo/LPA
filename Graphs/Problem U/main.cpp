// C++ program to find out whether a 
// given graph is Bipartite or not 
#include <iostream> 
#include <queue> 
#define MAX_VERTEX 100
using namespace std; 


int n_vertex;
int G[MAX_VERTEX][MAX_VERTEX];

// This function returns true if  
// graph G[V][V] is Bipartite, else false 
bool isBipartiteUtil(int src, int colorArr[]) 
{ 
    colorArr[src] = 1; 
  
    // Create a queue (FIFO) of vertex numbers a 
    // nd enqueue source vertex for BFS traversal 
    queue <int> q; 
    q.push(src); 
  
    // Run while there are vertices in queue (Similar to BFS) 
    while (!q.empty()) 
    { 
        // Dequeue a vertex from queue ( Refer http://goo.gl/35oz8 ) 
        int u = q.front(); 
        q.pop(); 
  
        // Return false if there is a self-loop  
        if (G[u][u] == 1) 
        return false;  
  
        // Find all non-colored adjacent vertices 
        for (int v = 0; v < n_vertex; ++v) 
        { 
            // An edge from u to v exists and 
            // destination v is not colored 
            if (G[u][v] && colorArr[v] == -1) 
            { 
                // Assign alternate color to this 
                // adjacent v of u 
                colorArr[v] = 1 - colorArr[u]; 
                q.push(v); 
            } 
  
            // An edge from u to v exists and destination 
            // v is colored with same color as u 
            else if (G[u][v] && colorArr[v] == colorArr[u]) 
                return false; 
        } 
    } 
  
    // If we reach here, then all adjacent vertices can 
    // be colored with alternate color 
    return true; 
} 
  
// Returns true if G[][] is Bipartite, else false 
bool isBipartite() 
{ 
    // Create a color array to store colors assigned to all 
    // veritces. Vertex/ number is used as index in this 
    // array. The value '-1' of colorArr[i] is used to 
    // ndicate that no color is assigned to vertex 'i'. 
    // The value 1 is used to indicate first color is 
    // assigned and value 0 indicates second color is 
    // assigned. 
    int colorArr[n_vertex]; 
    for (int i = 0; i < n_vertex; ++i) 
        colorArr[i] = -1; 
  
    // This code is to handle disconnected graoh 
    for (int i = 0; i < n_vertex; i++) 
    if (colorArr[i] == -1) 
        if (isBipartiteUtil( i, colorArr) == false) 
        return false; 
  
    return true; 
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

	if(isBipartite()){
        cout << "True"<<endl;
    }
    else{
        cout << "False"<<endl;
    } 
	return 0; 
} 

