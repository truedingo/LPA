// A C++ program to check if two given line segments intersect 
//g++ -Wall -std=c++11 intersection.cpp -o intersection
#include <iostream> 
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
  
int ind = 3;
int intersections = 0;

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
  
    if (val == 0) return 0;  // colinear 
  
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

/*int n_intersect(vector<vector<int>> points,int iterations, int beg, int end){

    if(iterations>=0){
        cout<<"Initial Point: "<<beg<<endl;
        cout<<"End Point: "<<end<<endl;
        iterations--;
        int ant_beg = beg;
        int ant_end = end; 
        beg = beg+2;
        end = end+2;

        if(doIntersect(points.at(ant_beg), points.at(ant_end),points.at(beg), points.at(end))){
            cout<<"interceptei!"<<endl;
        }
        n_intersect(points,iterations,beg,end);
    }

    else{
        cout<<"Line completed!"<<endl;
    }
}
*/

void n_intersect(vector<vector<int>> points,int iterations){

    //iteractions = 2 temporario
    if(iterations>0){
        //starting on 3 
        cout<<"Ind: "<<ind<<endl;
        cout<<"Iterations: "<<iterations<<endl;
        //reta 2
        Point p1;
        p1.x = points[ind][0];
        p1.y = points[ind][1];
        cout<<"P1- x: "<<p1.x<<" y: "<< p1.y<<endl;
       
        Point p2;
        p2.x = points[ind-1][0];
        p2.y = points[ind-1][1];
        cout<<"P2 - x: "<< p2.x<<" y: "<<p2.y<<endl;

        //reta 1
        Point p3;
        p3.x = points[ind-2][0];
        p3.y = points[ind-2][1];
        cout<<"P3 - x: "<<p3.x<<" y: "<<p3.y<<endl;
    
        Point p4;
        p4.x = points[ind-3][0];
        p4.y = points[ind-3][1];
        cout<<"P4- x: "<<p4.x<<" y: "<<p4.y<<endl;

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

  
// Driver program to test above functions 
int main() 
{ 
    vector<vector<int> > points = {{5,9},{7,8},{5,9},{7,5},{7,5},{2,5},{1,4},{2,3}};
    int iterations = points.size()/4;

    n_intersect(points,iterations);

    cout<<"Number of intersections: "<<intersections<<endl;

    
    return 0; 
} 