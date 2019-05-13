#include<iostream>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <cstring>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

#define MAX_CONNECTIONS 1000

typedef struct Node{
  int x,y;
}Node;

typedef struct Connection{
  int source, target;
  double weight;
}Connection;

int n_nodes;
int n_connections;
vector<Node> coordinates_vector;
Connection connections[MAX_CONNECTIONS];

void calculateWeight(){
  for(int i=0;i<n_connections;i++){
    connections[i].weight= (double) sqrt( fabs(coordinates_vector[connections[i].source -1].x -coordinates_vector[connections[i].target -1].x) * fabs(coordinates_vector[connections[i].source -1].x - coordinates_vector[connections[i].target -1].x) + fabs(coordinates_vector[connections[i].source -1].y - coordinates_vector[connections[i].target -1].y) * fabs(coordinates_vector[connections[i].source -1].y - coordinates_vector[connections[i].target -1].y));
    cout<<connections[i].weight<<endl;
   
  }
}


int main(){
  while(scanf("%d",&n_nodes)!=EOF){
    for (int i=0;i<n_nodes;i++){
      Node node;
      cin>>node.x>>node.y;
      coordinates_vector.push_back(node);
    }
   cin>>n_connections;
   for(int m=0;m<n_connections;m++){
     Connection conn;
      cin>>conn.source>>conn.target;
      connections[m] = conn;
      calculateWeight();
   }
  
  }
  
}