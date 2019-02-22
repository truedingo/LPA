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
} Point;

typedef struct line
{
    Point source;
    Point target;
} Line;

typedef struct pairs
{
    int source;
    int target;
} Pairs;

int n_places;
int n_devices;
int n_colliders;
Point coordinates[MAX_COORDINATES];
Pairs pairs[MAX_COLLIDERS];
int devices[MAX_DEVICES];
bool places_used[MAX_COORDINATES];
int d_place[MAX_COORDINATES];
int count_intersections;
int min_intersections;

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

void recursive()
{
    if (count_intersections >= min_intersections && n_devices <= n_devices)
        return;
}

int main()
{
    int i;
    cin >> n_places;

    for (i = 0; i < n_places; i++)
    {
        Point p;
        cin >> p.x >> p.y;
        coordinates[i] = p;
    }

    cout << "Coordinates vector: " << endl;
    cout << " " << endl;

    for (i = 0; i < n_places; i++)
    {
        cout << "X: " << coordinates[i].x << " Y: " << coordinates[i].y << endl;
    }

    cout << " " << endl;
    cout << "End of Coordinates vector" << endl;

    cin >> n_devices >> n_colliders;

    for (i = 0; i < n_devices; i++)
    {
        devices[i] = i + 1;
    }

    for (i = 0; i < n_colliders; i++)
    {
        Pairs pair;
        cin >> pair.source >> pair.target;
        pairs[i] = pair;
    }
    cout << "Pairs of Source and Targets: " << endl;
    cout << " " << endl;

    for (i = 0; i < n_colliders; i++)
    {
        cout << "Source: " << pairs[i].source << "   -->   Target: " << pairs[i].target << endl;
    }
    cout << "End of Pairs of Source and Targets" << endl;
    cout << " " << endl;

    for (i = 0; i < n_places; i++)
    {

        for (int j = 0; j < n_devices; j++)
        {
            places_used[i] = true;
            d_place[j] = i;
            recursive();
            d_place[j] = 0;
            places_used[i] = false;
        }
    }

    return 0;
}