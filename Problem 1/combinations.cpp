// Program to print all combination of size r in an array of size n 
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector> 
using namespace std;

void print(vector<vector<int> > v)
{   
    cout<<"New case";
    for (vector<int> e: v) {
       
        cout << "(" << e[0]<<","<<e[1]<<")"<<endl;
    }
    cout << std::endl;
}

int main()
{
    vector<vector<int> > v = { {1,1},{2,5},{3,9}};
    // vector should be sorted at the beginning.

    do {
        print(v);
    } while (next_permutation(v.begin(), v.end()));
}