#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

#define MAX_N 1000
#define MAX_M 2000
#define MAXINT 1000000

typedef struct wormhole{
    int x;
    int y;
    int t;
}wormholes;

int n_test_cases;
 int n, m;
vector<wormholes> wormhole_vector;
vector<string> solutions;

void bellmanFord(vector<wormholes> wormhole_vector, int src){
    int dist[MAX_N];
    bool is_possible=false;;
    for (int v=0; v< n;v++)
        dist[v]=MAXINT;
    
    dist[src] = 0;

    for (int i = 1; i < n-1; i++) { 
        for (int j = 0; j < m; j++) { 
            int u = wormhole_vector[i].x; 
            int v = wormhole_vector[i].y; 
            int weight = wormhole_vector[i].t; 
            if (dist[v]>dist[u]+weight) 
                dist[v] = dist[u] + weight; 
        } 
    } 

    for (int i = 0; i < m; i++)  { 
        int u = wormhole_vector[i].x; 
        int v = wormhole_vector[i].y; 
        int weight = wormhole_vector[i].t; 
        if (dist[v]>dist[u]+weight) 
            is_possible=false;
        else
            is_possible=true;
    } 
    if(!is_possible)
        solutions.push_back("possible");
    else{
        solutions.push_back("not possible");
    }
}


int main(){
    cin >> n_test_cases;
    for(int j=0;j<n_test_cases;j++){
       
        cin>>n>>m;
        
        for(int i=0; i<m;i++){
            wormholes worm;
            cin>>worm.x>>worm.y>>worm.t;
            wormhole_vector.push_back(worm);
        }
        /*for(int i=0;i<wormhole_vector.size();i++){
            cout<<wormhole_vector[i].x<<" " <<wormhole_vector[i].y<<" "<<wormhole_vector[i].t<<endl;;
        }*/
        bellmanFord(wormhole_vector,0);

        wormhole_vector.clear();
    }

    for(int i=0;i<(int) solutions.size();i++){
        cout<<solutions[i]<<endl;
    }
    return 0;
}