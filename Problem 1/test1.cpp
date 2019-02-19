#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector> 
using namespace std;


  
/* Function to print permutations of string 
   This function takes three parameters: 
   1. String 
   2. Starting index of the string 
   3. Ending index of the string. */
void permute(vector<vector<int> > v, int l, int r) 
{ 
   int i; 
   if (l == r) {
    for (vector<int> e: v) {
       
        cout << "(" << e[0]<<","<<e[1]<<")"<<endl;
    }
    cout << endl;
    }
   else
   { 
       for (i = l; i <= r; i++) 
       { 
          swap(v[l], v[i]); 
          permute(v, l+1, r); 
          swap(v[l], v[i]); //backtrack 
       } 
   } 
} 
  
/* Driver program to test above functions */
int main() 
{ 
    char str[] = "ABC"; 
    vector<vector<int> > v = { {1,1},{2,5},{3,9}};
    int n = strlen(str); 
    permute(v, 0, n-1); 
    return 0; 
} 