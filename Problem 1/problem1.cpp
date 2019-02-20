#include <iostream>
#include <string>
#include <vector>
#include <array>
//g++ -Wall -std=c++11 problem1.cpp -o problem1
 
using namespace std;

int n_devices;
int n_colliders;
 
//n is vector size, k is arrangement size
void permute(vector<vector<int> > v, int n, int k, vector<vector<vector<int> > >solutions)
{
   if (k == 0) {
       vector<vector<int> >permut;
        for (int i=n; i< v.size(); i++) {
            permut.push_back(v[i]);
           
            
        }
        for(int m=0; m<permut.size(); m++){
            cout<<permut[m][0]<<" "<<permut[m][1]<<endl;
        }
        cout<<endl;
        solutions.push_back(permut);
        
    }
    for (int j=0; j< n; j++)
    { 
        swap(v[j], v[n-1]); 
        permute(v, n-1, k-1, solutions);
        swap(v[j], v[n-1]); //backtrack 
    }
}


int main(){
    int i;
    int x;
    int y;
    int source_device;
    int target_device;
    int n_places;

    cin >> n_places;
    vector<vector<int> > coord_vector;
    vector<int> coordinates;
    vector<vector<int> > pairs_vector;
    vector<int> pairs;

    for(i=0; i<n_places; i++){
        cin>>x>>y;
        coordinates.push_back(x);
        coordinates.push_back(y);
        coord_vector.push_back(coordinates);
        coordinates.clear();

    }

    cout<<"Coordinates vector: "<<endl;
    cout<<" "<<endl;
    for(i=0; i<coord_vector.size(); i++){
            cout<< "x: "<<coord_vector[i][0] << " y: " <<coord_vector[i][1]<<endl;
    }                                                                   
 
    cout<<" "<<endl;
    cout<<"End of Coordinates vector"<<endl;
   
    cin>>n_devices>>n_colliders;

    for(i=0;i<n_colliders;i++){
        cin>>source_device>>target_device;
        pairs.push_back(source_device);
        pairs.push_back(target_device);
        pairs_vector.push_back(pairs);
        pairs.clear();
 
    }
    cout<<"Pairs of Source and Targets: "<<endl;
    cout<<" "<<endl;

    for(i=0; i<pairs_vector.size(); i++){
        cout<< "Source: "<<pairs_vector[i][0] << " Target: " <<pairs_vector[i][1]<<endl;
    }
    cout<<"End of Pairs of Source and Targets"<<endl;
    cout<<" "<<endl;
     int count=1;
     //permute(coord_vector, 0, n_places-1,count,n_devices,0);
     vector<vector<vector<int> > >solutions;
     permute(coord_vector, coord_vector.size(), n_devices, solutions);
     cout<<"sol size is: "<<solutions.size()<<endl;
    return 0;
}