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
int graph1[26][26];
int graph2[26][26];
bool C1[26][26];
bool C2[26][26];
int n1,n2;

void reset(){
  for(int i = 0; i < 26; i++){
    for(int j = 0; j < 26; j++){
      graph1[i][j] = 0;
      graph2[i][j] = 0;
      C1[i][j] = false;
      C2[i][j] = false;
    }
  }
}

void floyd_warshall(){

  for(int i = 0; i < 26; i++){
    for(int j = 0; j < 26; j++){
      if(graph1[i][j] == 1){
        C1[i][j] = true;
      }
      if(graph2[i][j] == 1){
        C2[i][j] = true;
      }
    }
  }
  for(int k = 0; k < 26; k++){
    for(int i = 0; i < 26; i++){
      for(int j = 0; j < 26; j++){
        if(C1[i][k] && C1[k][j]){
          C1[i][j] = true;
        }
        if(C2[i][k] && C2[k][j])
        {
          C2[i][j] = true;
        }
      }
    }
  }
}

bool compare_graphs(){
  for(int i = 0; i < 26; i++){
    for(int j = 0; j < 26; j++){
      if(C1[i][j] != C2[i][j]){
        return false;
      }
    }
  }
  return true;
}

void printMatrix(){
  for (int i=0;i<26;i++){
    for(int j=0;j<26;j++){
      cout<<graph1[i][j]<<" ";
    }
    cout<<endl;
  }
  cout<<endl;
  cout<<"Graph 2"<<endl;
  cout<<endl;
    for (int i=0;i<26;i++){
    for(int j=0;j<26;j++){
      cout<<graph2[i][j]<<" ";
    }
    cout<<endl;
  }
}

int main(){
  int ncases;
  char c1, c2;
  scanf("%d",&ncases);
  for(int k = 0; k < ncases; k++){
    reset();

    scanf("%d",&n1);
    for(int i = 0; i < n1; i++){
      scanf(" %c %c",&c1,&c2);
      int p1, p2;
      p1 = c1 - 65;
     
      p2 = c2 - 65;
      
      graph1[p1][p2] = 1;
     
    }
    scanf("%d",&n2);
    for(int i = 0; i < n2; i++){
      scanf(" %c %c",&c1,&c2);
      int p1, p2;
      p1 = c1 - 65;
      p2 = c2 - 65;
      graph2[p1][p2] = 1;
      
    }
    floyd_warshall();

    if(compare_graphs())
      printf("YES\n");
    else{
      printf("NO\n");
    }

    if(k < ncases-1){
      printf("\n");
    }
    
  }

  //printMatrix();
  return 0;
}
