#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <chrono> 
#include <math.h> 
//g++ -Wall -std=c++11 problem1.cpp -o problem1
 
using namespace std;
using namespace std::chrono;
int n_devices;
int n_colliders;
int i;
int x;
int y;
int source_device;
int target_device;
int n_places;
vector<vector<int> > coord_vector;
vector<int> coordinates;
vector<int>pairs_vector;

//permute uses vector size and number of devices
void permute(vector<vector<int> > v, int n_places, int n_devices)
{
   if (n_devices == 0) {
       vector<vector<int> >permut;
        for (int i=n_places; i< coord_vector.size(); i++) {
            permut.push_back(v[i]);
           
            
        }
        for(int m=0; m<permut.size(); m++){
            cout<<permut[m][0]<<" "<<permut[m][1]<<" ";
        }
        cout<<endl;
    }
    for (int j=0; j< n_places; j++)
    { 
        swap(coord_vector[j], coord_vector[n_places-1]); 
        permute(coord_vector, n_places-1, n_devices-1);
        swap(v[j], v[n_places-1]); //backtrack 
    }
}

vector<vector<int>> makeConnections(vector<vector<int>>connVector){
	for(int i=0; i<connVector.size(); i++){
        connVector[i] = coord_vector[pairs_vector[i]-1];
    }
    return connVector;
}

void printConnectionVector(vector<vector<int>>connVector){
    for(int i=0; i<connVector.size(); i++){
        cout<<"("<<connVector[i][0]<<","<<connVector[i][1]<<")"<<" ";
    }
}

int main(){
   
    cin >> n_places;

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
        pairs_vector.push_back(source_device);
        pairs_vector.push_back(target_device);
 
    }
    cout<<"Pairs of Source and Targets: "<<endl;
    cout<<" "<<endl;

    for(i=0; i<pairs_vector.size(); i++){
        cout<< "Source: "<<pairs_vector[i]<< " Target: " <<pairs_vector[i]<<endl;
    }
    cout<<"End of Pairs of Source and Targets"<<endl;
    cout<<" "<<endl;


    auto start = high_resolution_clock::now();

    permute(coord_vector, coord_vector.size(), n_devices);

    vector<vector<int>>connection_vector(pairs_vector.size(), vector<int>(2,0));
    connection_vector = makeConnections(connection_vector);
	printConnectionVector(connection_vector);

    auto stop = high_resolution_clock::now(); 
    auto duration = duration_cast<microseconds>(stop - start); 
    cout << duration.count() * pow(10,-6)<<" seconds"<< endl; 
    return 0;
}