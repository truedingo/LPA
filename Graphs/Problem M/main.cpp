#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;


struct person{
    char name[50];
    int id;
};


int nnodes,nconn;
vector<vector<int> > graph;
vector<person> persons;
int global;

vector<vector<int> > init_matrix(int m, int n){
	vector<vector<int> > matrix(m, vector<int>(n,0));
	return matrix;
}

int reid(char name[]){
    for(int i = 0; i < nnodes; i++){
        if(strcmp(name,persons[i].name) == 0){
            return persons[i].id;
        }
    }

    return -1;
}

void dfs(int node, bool vis[]) 
{ 
    // Mark as visited 
    vis[node] = true; 
  
    // Traverse for all its children 
    for (int i = 0; i < nnodes; i++) { 
  
        // If not visited 
        if (graph[node][i] && !vis[i]){
            dfs(i, vis); 
            global++; 
        } 
  
    } 
} 

int findLongestPath(int n) 
{ 
    int aux = 0;
    // Visited array to know if the node 
    // has been visited previously or not 
    bool vis[n + 1]; 
    memset(vis, false, sizeof vis); 
  
    // Call DFS for every unvisited vertex 
    for (int i = 1; i <= n; i++) { 
        if (!vis[i]) 
            dfs(i, vis);
            if(global > aux){
                aux = global;
            }
            global = 1;
    } 
  
  
    // Traverse and find the maximum of all dp[i] 

    return aux; 
} 

int main(){
    char p1[50], p2[50];
    int id = 0,id1,id2;

    global = 1;

    scanf("%u %u", &nnodes, &nconn);

    for (int i = 0; i < nnodes; i++){
        person Person;

        scanf("%s",Person.name);


        Person.id = id;

        persons.push_back(Person);

        id++;
    }


    graph = init_matrix(nnodes+1,nnodes+1);

    for (int i = 1; i <= nconn; i++){
        scanf("%s %s",p1,p2);

        id1 = reid(p1);
        id2 = reid(p2);

        graph[id1][id2] = 1;
        graph[id2][id1] = 1;
    }


    cout << findLongestPath(nnodes) << "\n"; 

    return 0;

}