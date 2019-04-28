// Program to print BFS traversal from a given 
// source vertex. BFS(int s) traverses vertices 
// reachable from s. 
#include<iostream> 
#include <list> 
#define MAX_VERTEX 100
using namespace std; 


int n_vertex;
int G[MAX_VERTEX][MAX_VERTEX];
// This class represents a directed graph using 
// adjacency list representation 
class Graph 
{ 
	int V; // No. of vertices 

	// Pointer to an array containing adjacency 
	// lists 
	list<int> *adj; 
public: 
	Graph(int V); // Constructor 

	// function to add an edge to graph 
	void addEdge(int v, int w); 

	// prints BFS traversal from a given source s 
	int BFS(int s); 
}; 

Graph::Graph(int V) 
{ 
	this->V = V; 
	adj = new list<int>[V]; 
} 

void Graph::addEdge(int v, int w) 
{ 
	adj[v].push_back(w); // Add w to v’s list. 
} 

int Graph::BFS(int s) 
{ 
	// Mark all the vertices as not visited 
    int solution=1;
	bool visited[MAX_VERTEX]; 
	for(int i = 0; i < n_vertex; i++) 
		visited[i] = false; 

	// Create a queue for BFS 
	list<int> queue; 

	// Mark the current node as visited and enqueue it 
	visited[s] = true; 
	queue.push_back(s); 

	// 'i' will be used to get all adjacent 
	// vertices of a vertex 
	list<int>::iterator u; 

	while(!queue.empty()) 
	{ 
		// Dequeue a vertex from queue and print it 
		int t = queue.front(); 
		//cout << t <<endl; 
		queue.pop_front(); 

		// Get all adjacent vertices of the dequeued 
		// vertex s. If a adjacent has not been visited, 
		// then mark it visited and enqueue it 
		for (u = adj[t].begin(); u != adj[t].end(); ++u) 
		{ 
            cout<<"T: "<<t<<" U: "<<*u<<endl;
			if (!visited[*u]) 
			{ 
				visited[*u] = true; 
				queue.push_back(*u); 
                if(*u==s)
                    solution++;
			} 
		} 
	} 
    return solution;
} 

// Driver program to test methods of graph class 
int main() 
{ 
     cin >> n_vertex;

	
	for (int i=0;i<n_vertex;i++){
        for (int j=0;j<n_vertex;j++){
            cin>>G[i][j];
        }
    }
	// Create a graph given in the above diagram 
	Graph g(n_vertex); 


    for (int i=0;i<n_vertex;i++){
        for (int j=0;j<n_vertex;j++){
            if(G[i][j]==1)
                g.addEdge(i,j);
        }
    }
	cout<<"solution: "<<g.BFS(0)<<endl; 

	return 0; 
} 

