#include <iostream>
#include <string>
#include <vector>
#include <array>
//g++ -Wall -std=c++11 problem1.cpp -o problem1
 
using namespace std;
 
typedef struct coordinates{
    int x;
    int y;
    int device;
}Coordinates;
 
typedef struct pairs{
    int source_device;
    int target_device;
}Pairs;

int n_devices;
int n_colliders;
 
 
 
void main_function(int devices, int index){
   
}
 
int main(){
    int i;
    int x;
    int y;
    int source_device;
    int target_device;
    int n_places;

    cin >> n_places;
    vector<vector<int>> coord_vector;
    vector<int> coordinates;
    vector<vector<int>> pairs_vector;
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
 
    return 0;
}