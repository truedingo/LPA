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

int n_cities;
int graph[500][500];
int dist[500][500];




void floydWarshall(){
    int i, j, k;

    for (i = 0; i < n_cities; i++) {
        for (j = 0; j < n_cities; j++) {
            dist[i][j] = graph[i][j];
        }
    }

    for (k = 0; k < n_cities; k++){
        // Pick all vertices as source one by one
        for (i = 0; i < n_cities; i++){
            // Pick all vertices as destination for the
            // above picked source
            for (j = 0; j < n_cities; j++){
                // If vertex k is on the shortest path from
                // i to j, then update the value of dist[i][j]
                if (dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
            }
        }
    }
    
}


int main(){
    int value, from, to;
    scanf("%d", &n_cities);
    for(int i=0; i< n_cities; i++){
         for(int j=0; j< n_cities; j++){
             scanf("%d", &value);
             if(value != -1){
                 graph[i][j] = value;
             }
             else{
                 graph[i][j] = 999999999;
             }
         }
    }
   

    floydWarshall();

    while (scanf("%d %d", &from, &to) != EOF) {
        cout <<dist[from-1][to-1] << endl;
    }

    return 0;
}
