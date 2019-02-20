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
int ind = 3;
int intersections = 0;
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

// Given three colinear points p, q, r, the function checks if 
// point q lies on line segment 'pr' 
bool onSegment(vector<int> p, vector<int> q, vector<int> r) 
{ 
	if (q[0] <= max(p[0], r[0]) && q[0] >= min(p[0], r[0]) && 
		q[1] <= max(p[1], r[1]) && q[1] >= min(p[1], r[1])) 
	return true; 

	return false; 
} 

// To find orientation of ordered triplet (p, q, r). 
// The function returns following values 
// 0 --> p, q and r are colinear 
// 1 --> Clockwise 
// 2 --> Counterclockwise 
int orientation(vector<int> p, vector<int> q, vector<int> r) 
{ 
	// See https://www.geeksforgeeks.org/orientation-3-ordered-points/ 
	// for details of below formula. 
	int val = (q[1] - p[1]) * (r[0] - q[0]) - 
			(q[0] - p[0]) * (r[1] - q[1]); 

	if (val == 0) return 0; // colinear 

	return (val > 0)? 1: 2; // clock or counterclock wise 
} 

// The main function that returns true if line segment 'p1q1' 
// and 'p2q2' intersect. 
bool doIntersect(vector<int > p1, vector<int > q1, vector<int > p2, vector<int > q2) 
{ 
	// Find the four orientations needed for general and 
	// special cases 
	int o1 = orientation(p1, q1, p2); 
	int o2 = orientation(p1, q1, q2); 
	int o3 = orientation(p2, q2, p1); 
	int o4 = orientation(p2, q2, q1); 

	// General case 
	if (o1 != o2 && o3 != o4) 
		return true; 

	// Special Cases 
	// p1, q1 and p2 are colinear and p2 lies on segment p1q1 
	if (o1 == 0 && onSegment(p1, p2, q1)) return true; 

	// p1, q1 and q2 are colinear and q2 lies on segment p1q1 
	if (o2 == 0 && onSegment(p1, q2, q1)) return true; 

	// p2, q2 and p1 are colinear and p1 lies on segment p2q2 
	if (o3 == 0 && onSegment(p2, p1, q2)) return true; 

	// p2, q2 and q1 are colinear and q1 lies on segment p2q2 
	if (o4 == 0 && onSegment(p2, q1, q2)) return true; 

	return false; // Doesn't fall in any of the above cases 
}

vector<vector<int> > makeConnections(vector<vector<int> >connVector){
	for(int i=0; i<connVector.size(); i++){
        connVector[i] = coord_vector[pairs_vector[i]-1];
    }
    return connVector;
}

void printConnectionVector(vector<vector<int> >connVector){
    for(int i=0; i<connVector.size(); i++){
        cout<<"("<<connVector[i][0]<<","<<connVector[i][1]<<")"<<" ";
    }
}

void n_intersect(vector<vector<int> > points,int iterations){
 
    //iteractions = 2 temporario
    if(iterations>0){
        //starting on 3
        cout<<"Ind: "<<ind<<endl;
        cout<<"Iterations: "<<iterations<<endl;
        //reta 2
        vector<int> p1;
        p1[0] = points[ind][0];
        p1[1] = points[ind][1];
        cout<<"P1- x: "<<p1[0]<<" y: "<< p1[1]<<endl;
       
        vector<int> p2;
        p2[0] = points[ind-1][0];
        p2[1] = points[ind-1][1];
        cout<<"P2 - x: "<< p2[0]<<" y: "<<p2[1]<<endl;
 
        //reta 1
        vector<int> p3;
        p3[0] = points[ind-2][0];
        p3[1] = points[ind-2][1];
        cout<<"P3 - x: "<<p3[0]<<" y: "<<p3[1]<<endl;
   
        vector<int> p4;
        p4[0] = points[ind-3][0];
        p4[1] = points[ind-3][1];
        cout<<"P4- x: "<<p4[0]<<" y: "<<p4[1]<<endl;
 
        if(doIntersect(p1,p2,p3,p4)){
            //cout <<"intersected!!!"<<endl;
            intersections ++;
        }
        iterations--;
        ind = ind+4;
        n_intersect(points,iterations);
    }
    else{
        return;
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

    vector<vector<int> >connection_vector(pairs_vector.size(), vector<int>(2,0));
    connection_vector = makeConnections(connection_vector);
	printConnectionVector(connection_vector);

    auto stop = high_resolution_clock::now(); 
    auto duration = duration_cast<microseconds>(stop - start); 
    cout << duration.count() * pow(10,-6)<<" seconds"<< endl; 
    return 0;
}