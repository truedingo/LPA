// C++ program to find out whether a 
// given graph is Bipartite or not 
#include <iostream> 
#include <vector>
#include <queue> 
#define MAX_SEQUENCES 300
#define MAX_PAIRWISE 5000

using namespace std; 

int n_pairwises;
int n_sequences;
int sequences[MAX_PAIRWISE][2];
vector<vector<int> > adj;

vector<vector<int> > init_graph(int n){
  vector<vector<int> > m(n,vector<int>(n,0));
  return m;
}

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
        if (adj[u][u] == 1) 
        return false;  
  
        // Find all non-colored adjacent vertices 
        for (int v = 0; v < n_sequences; ++v) 
        { 
            // An edge from u to v exists and 
            // destination v is not colored 
            if (adj[u][v] && colorArr[v] == -1) 
            { 
                // Assign alternate color to this 
                // adjacent v of u 
                colorArr[v] = 1 - colorArr[u]; 
                q.push(v); 
            } 
  
            // An edge from u to v exists and destination 
            // v is colored with same color as u 
            else if (adj[u][v] && colorArr[v] == colorArr[u]) 
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
    int colorArr[n_sequences]; 
    for (int i = 0; i < n_sequences; ++i) 
        colorArr[i] = -1; 
  
    // This code is to handle disconnected graoh 
    for (int i = 0; i < n_sequences; i++) 
    if (colorArr[i] == -1) 
        if (isBipartiteUtil( i, colorArr) == false) 
        return false; 
  
    return true; 
} 


// Driver program to test above function 
int main() 
{ 
   while(!cin.eof()){
        cin>>n_sequences>>n_pairwises;

        adj= init_graph(n_sequences);

        for(int i=0;i<n_pairwises;i++){
            cin>>sequences[i][0]>>sequences[i][1];
            //cout<<sequences[i][0]<<" "<<sequences[i][1]<<endl;
            adj[sequences[i][0]-1][sequences[i][1]-1]=1;
            adj[sequences[i][1]-1][sequences[i][0]-1]=1;
        }
        
        /*
        for(int i=0;i<n_sequences;i++){
            for(int j=0;j<n_sequences;j++){
                cout<<adj[i][j]<<" ";
            }
            cout<<endl;
        }*/

        if(isBipartite())
            cout<<"No"<<endl;
        else
            cout<<"Yes"<<endl;
        

        


   }

	return 0; 
} 

