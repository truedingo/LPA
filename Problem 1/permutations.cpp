#include <string>
#include <vector>
#include <array>
// next_permutation example
#include <iostream>     // std::cout
#include <algorithm>    // std::next_permutation, std::sort
#include <list>
#include <numeric>
#include <random>

//g++ -Wall -std=c++11 permutations.cpp -o perm

using namespace std;

void PermGenerator(int n, int k, vector<vector<int>>vec)
{
    for(int j=0; j < vec.size(); j++){
        cout<<vec[j][0]<<" "<<vec[j][1]<<endl;
    }
    cout << "These are the Possible Permutations: " << endl;
    do
    {
        for (int i = 0; i < k; i++)
        {
            cout<<vec[i][0]<<" "<<vec[i][1]<<endl;
        }
        cout << endl;
        std::reverse(vec.begin()+k,vec.end());
    } while (next_permutation(vec.begin(),vec.end()));
}

int main(){
    //vector<vector<int> > v = { {1,1},{2,5},{3,9}};
    vector<int> test;
    vector<vector<int> > test2;
    test.push_back(1);
    test.push_back(1);
    test2.push_back(test);
    test.clear();
    test.push_back(2);
    test.push_back(5);
    test2.push_back(test);
    test.clear();
    test.push_back(3);
    test.push_back(9);
    test2.push_back(test);
    test.clear();
    PermGenerator(test2.size(), 3, test2);

}