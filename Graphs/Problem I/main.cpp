// C++ program to find out whether a 
// given graph is Bipartite or not 
#include <iostream> 
#include <queue> 
#define MAX_SEQUENCES 300
#define MAX_PAIRWISE 5000

using namespace std; 

int n_pairwises;
int n_sequences;
int sequences[MAX_PAIRWISE][MAX_PAIRWISE];

// Driver program to test above function 
int main() 
{ 
   while(!cin.eof()){
        cin>>n_sequences>>n_pairwises;
        for(int i=0;i<n_pairwises;i++){
            cin>>sequences[i][j];
        }


   }

	return 0; 
} 

