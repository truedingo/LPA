#include<iostream>
#include <vector>
#include <iostream>

using namespace std;

#define MAX_VERTEX 100

int graph[MAX_VERTEX][MAX_VERTEX];
int vertexes;
int visited[MAX_VERTEX];
vector<int> result_cycle;
int best =  9999999;;
int actual_vertex;

void print_result(){
  for(int i=0;i<(int)result_cycle.size();i++){
    cout << result_cycle[i] << " ";
  }
  cout << endl;
}

void DFS(int vertex){
  visited[vertex] = 1;
  if((int)result_cycle.size() >= best){
    return;
  }
  for(int i=0; i < vertexes; i++){
    if(graph[vertex][i]){
      if(i == actual_vertex){
        if((int)result_cycle.size() < best){
          best = (int)result_cycle.size();
          return;
        }
      }
      if(!visited[i]){
        result_cycle.push_back(i);
        DFS(i);
        result_cycle.pop_back();
        visited[i] = 0;
      }
    }
  }
}

int main(){
  int value;
  
  cin>>vertexes;
  for(int i=0;i<vertexes; i++){
    for(int j=0;j<vertexes; j++){
      cin>>value;
      graph[i][j] = value;
    }
  }

  for(int i=0;i<vertexes; i++){

    for(int j=0;j<vertexes; j++){
      visited[j] = 0;
    }

    result_cycle.push_back(i);
    actual_vertex = i;
    DFS(i);
    result_cycle.clear();

  }

  cout << best << endl;

  return 0;
}
