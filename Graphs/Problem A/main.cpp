#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
#define DEBUGe

#define MAXINT 100000


vector<vector<int> >  graph;
int finish_place ;
int n;

vector<vector<int> > init_graph(int n){
  vector<vector<int> > m(n,vector<int>(n));
  return m;
}

int print_graph() {
   for (int i = 0; i < (int)graph.size(); i++){
     for(int j=0; j< (int)graph[i].size(); j++){
       cout << graph[i][j] << endl;
     }
     cout << endl;
   }
   return 0;
}

int min_distance(int dist[], bool sptSet[])
{
   // Initialize min value
   int min = MAXINT;
   int min_index;

   for (int v = 0; v < n; v++)
     if (sptSet[v] == false && dist[v] <= min){
      min = dist[v];
      min_index = v;
     }

   return min_index;
}



int dijkstra(){
  int dist[n];
  bool sptSet[n];
  for (int i = 0; i < n; i++){
    dist[i] = MAXINT;
    sptSet[i] = false;
  }
  dist[0] = 0;

  for (int count = 0; count < n-1; count++) {

    int u = min_distance(dist, sptSet);

    sptSet[u] = true;

    if(finish_place == u)
      break;

    for (int v = 0; v < n; v++) {
      if (!sptSet[v] && graph[u][v]>0 && dist[u] != MAXINT  && dist[u]+graph[u][v] < dist[v]){
        dist[v] = dist[u] + graph[u][v];
      }
    }
  }
  
  return dist[finish_place];
}

int main() {
  int id;

 

  cin>>n;
  cin>>finish_place;
  finish_place = finish_place-1;
  graph = init_graph(n);
  for(int i=0;i<n;i++){
    cin>>id;
    for(int j=0;j<n;j++){
      cin>>graph[i][j] ;
    }
  }
  cout<<dijkstra()<<endl;
  return 0;
}
