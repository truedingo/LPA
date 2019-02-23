#include <iostream>
#include <string>
#include <vector>
#include <array>

#define MAX_COORDINATES 81
#define MAX_DEVICES 81
#define MAX_COLLIDERS 28

using namespace std;

typedef struct point
{
    int x;
    int y;
    int id;
} Point;

typedef struct line
{
    Point source;
    Point target;
} Line;

int n_places;
int n_devices;
int n_colliders;

Point coordinates[MAX_COORDINATES];
int adjacencies[MAX_DEVICES];
bool places_used[MAX_COORDINATES];
int d_place[MAX_COORDINATES];

vector<Line> lines;

int best_case=1;

void printCoordinates()
{
    int i;
    cout << "Coordinates vector: " << endl;
    cout << " " << endl;

    for (i = 0; i < n_places; i++)
    {
        cout << "X: " << coordinates[i].x << " Y: " << coordinates[i].y << endl;
    }

    cout << " " << endl;
    cout << "End of Coordinates vector" << endl;
    cout << endl;
}

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

    if (val == 0)
        return 0; // colinear

    return (val > 0) ? 1 : 2; // clock or counterclock wise
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

    // Caso de colinearidade entre target points do professor
    if ((p1.x == p2.x and p1.y == p2.y) or (p1.x == q2.x and p1.y == q2.y) or (q1.x == p2.x and q1.y == p2.y) or (q1.x == q2.x and q1.y == q2.y))
    {
        //cout<<"ENTREI AQUI!"<<endl;
        return false;
    }

    // p1, q1 and p2 are colinear and p2 lies on segment p1q1
    if (o1 == 0 && onSegment(p1, p2, q1))
        return true;

    // p1, q1 and q2 are colinear and q2 lies on segment p1q1
    if (o2 == 0 && onSegment(p1, q2, q1))
        return true;

    // p2, q2 and p1 are colinear and p1 lies on segment p2q2
    if (o3 == 0 && onSegment(p2, p1, q2))
        return true;

    // p2, q2 and q1 are colinear and q1 lies on segment p2q2
    if (o4 == 0 && onSegment(p2, q1, q2))
        return true;

    return false; // Doesn't fall in any of the above cases
}

int countIntersections(Line line, vector<Line> lines)
{
    int count = 0;
    for (int i = 0; i < (int)lines.size(); i++)
    {
        if (doIntersect(line.source, line.target, lines[i].source, lines[i].target))
            count++;
    }
    return count;
}

void recursive(int device)
{
    int count_intersections = 0;
    cout << "I'm on device " << device << endl;

    if (count_intersections >= best_case and device <= n_devices){
        return;
    }
    if (adjacencies[device] == 0)
    {
        device = device + 1;
        if (d_place[device] != 0)
            recursive(device);
        else
            for (int i = 0; i < n_places; i++)
            {
                if (places_used[i] == false)
                {
                    d_place[device] = i;
                    recursive(device);
                    d_place[device] = 0;
                }
            }
    }
    else
    {
        if (adjacencies[device] != 0)
        {   
            Line new_line;
            new_line.source = coordinates[d_place[device]];
            new_line.target = coordinates[adjacencies[device]];
            count_intersections = countIntersections(new_line, lines);
            cout<<count_intersections<<endl;
            lines.push_back(new_line);
            recursive(device);
            lines.pop_back();
        }
        else
        {
            for (int i = 0; i < n_places; i++)
            {
                if (places_used[i] == false)
                {
                    Line new_line;
                    new_line.source = coordinates[d_place[device]];
                    new_line.target = coordinates[adjacencies[device]];
                    count_intersections = countIntersections(new_line, lines);
                    d_place[adjacencies[device]] = i;
                    lines.push_back(new_line);
                    recursive(device);
                    d_place[adjacencies[device]] = 0;
                    lines.pop_back();
                }
            }
        }
    }
}

int main()
{
    int i;
    cin >> n_places;

    //cout<<"Number of places: "<<n_places<<endl;

    for (i = 1; i <= n_places; i++)
    {
        Point p;
        cin >> p.x >> p.y;
        coordinates[i] = p;
    }

    //printCoordinates();

    cin >> n_devices >> n_colliders;

    //cout<<"Number of devices: "<<n_devices<<endl;
    //cout<<"Number of colliders: "<<n_colliders<<endl;

    for (i = 1; i <= n_colliders; i++)
    {
        int source, target;
        cin >> source >> target;

        //coloca no vector de adjacencias os targets(d2) de d1
        adjacencies[source] = target;
    }

    for (i = 1; i <= n_places; i++)
    {
        for (int j = 1; j <= n_devices; j++)
        {
            //ponto esta a ser usado neste instante
            places_used[i] = true;
            ///cout<<"place "<<i<< " used!!"<<endl;
            d_place[j] = i;
            //cout<<"device number  "<<j<< " associated with place "<<i<<endl;

            //cout<<"doing recursive..."<<endl;
            recursive(j);
            d_place[j] = 0;
            places_used[i] = false;
        }
    }

    return 0;
}
