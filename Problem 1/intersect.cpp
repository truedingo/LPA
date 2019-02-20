// A C++ program to check if two given line segments intersect 
#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <chrono> 
#include <math.h> 
 
using namespace std; 

struct Point 
{ 
	int x; 
	int y; 
}; 

// Given three colinear points p, q, r, the function checks if 
// point q lies on line segment 'pr' 
bool onSegment(Point p, Point q, Point r) 
{ 
	if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) && 
		q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y)) 
	return true; 

	return false; 
} 

// To find orientation of ordered triplet (p, q, r). 
// The function returns following values 
// 0 --> p, q and r are colinear 
// 1 --> Clockwise 
// 2 --> Counterclockwise 
int orientation(Point p, Point q, Point r) 
{ 
	// See https://www.geeksforgeeks.org/orientation-3-ordered-points/ 
	// for details of below formula. 
	int val = (q.y - p.y) * (r.x - q.x) - 
			(q.x - p.x) * (r.y - q.y); 

	if (val == 0) return 0; // colinear 

	return (val > 0)? 1: 2; // clock or counterclock wise 
} 

// The main function that returns true if line segment 'p1q1' 
// and 'p2q2' intersect. 
bool doIntersect(Point p1, Point q1, Point p2, Point q2) 
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

vector<vector<int>> makeConnections(vector<vector<int>> coord_vector, vector<int> pairs_vector, vector<vector<int>>connVector){
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

// Driver program to test above functions 
int main() 
{
    vector<vector<int>>v = {{5,9}, {7,8}, {7,5}, {6,2}, {3,3}, {2,5}, {3,8}};
    int n_devices = 5;
    int n_colliders = 4;
    vector<int>pairs = {1,2,1,3,3,5,2,4};

	/*doIntersect(p1, q1, p2, q2)? cout << "Yes\n": cout << "No\n"; 

	p1 = {10, 0}, q1 = {0, 10}; 
	p2 = {0, 0}, q2 = {10, 10}; 
	doIntersect(p1, q1, p2, q2)? cout << "Yes\n": cout << "No\n"; 

	p1 = {-5, -5}, q1 = {0, 0}; 
	p2 = {1, 1}, q2 = {10, 10}; 
	doIntersect(p1, q1, p2, q2)? cout << "Yes\n": cout << "No\n";*/

     vector<vector<int>>connection_vector(pairs.size(), vector<int>(2,0));
     connection_vector = makeConnections(v, pairs, connection_vector);
	 printConnectionVector(connection_vector);



	return 0; 
} 
