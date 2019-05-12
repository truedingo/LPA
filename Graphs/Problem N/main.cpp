#include<iostream>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <queue>
#include <iostream>
#include <fstream>
#include <stack>
using namespace std;

int n_compounds;
int n_transformations;
int n_queries;
int graph[400][400];
int dist[400][400];




void floydWarshall(){
    int i, j, k;

    for (i = 0; i < n_compounds; i++) {
        for (j = 0; j < n_compounds; j++) {
            dist[i][j] = graph[i][j];
        }
    }

    for (k = 0; k < n_compounds; k++){
        // Pick all vertices as source one by one
        for (i = 0; i < n_compounds; i++){
            // Pick all vertices as destination for the
            // above picked source
            for (j = 0; j < n_compounds; j++){
                // If vertex k is on the shortest path from
                // i to j, then update the value of dist[i][j]
                if (dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
            }
        }
    }
    
}


int main(){
    int from, to;
    scanf("%d", &n_compounds);
    for(int i=0;i<n_compounds;i++){
        for(int j=0;j<n_compounds;j++){
            graph[i][j] = 999999999;
         }
    }

    scanf("%d",&n_transformations);

    for(int i=0;i< n_transformations;i++){
        int source=0,target=0,cost=0;
        cin>>source>>target>>cost;
        graph[source-1][target-1]=cost;
    }
   

    floydWarshall();
    cin>>n_queries;
    for(int i=0;i<n_queries;i++){
        scanf("%d %d", &from, &to);
        if(dist[from-1][to-1]==999999999)
            cout<<"Impossible!"<<endl;
        else
            cout <<dist[from-1][to-1] << endl;
    }
 

    return 0;
}
