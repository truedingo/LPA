#include <iostream>
#include <vector>

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

int n_coordinates;
int n_devices, n_devices_to_place;
int n_colliders;
int best_case;

Point coordinates[MAX_COORDINATES];
bool coordinates_used[MAX_COORDINATES];
int device_placed[MAX_COORDINATES];
bool device_to_use[MAX_DEVICES];
int intersections[MAX_DEVICES][MAX_DEVICES][MAX_DEVICES][MAX_DEVICES];
Line lines[MAX_COLLIDERS];
vector<int> adjacencies[MAX_DEVICES];

void printCoordinates()
{
    int i;
    cout << "Coordinates vector: " << endl;
    cout << " " << endl;

    for (i = 1; i <= n_coordinates; i++)
    {
        cout << "X: " << coordinates[i].x << " Y: " << coordinates[i].y << endl;
    }

    cout << " " << endl;
    cout << "End of Coordinates vector" << endl;
    cout << endl;
}

void print_coordinates_used()
{
    for (int i = 1; i <= n_coordinates; i++)
    {
        cout << "place " << i + 1 << ": " << coordinates_used[i] << endl;
    }
}

void print_device_placed()
{
    for (int i = 1; i <= n_coordinates; i++)
    {
        cout << "device: " << i + 1 << "on place: " << device_placed[i] << endl;
    }
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

// // The main function that returns true if line segment 'p1q1'
// // and 'p2q2' intersect.
int doIntersect(Point p1, Point q1, Point p2, Point q2)
{

    //Common point
    if (p1.id == p2.id || p1.id == q2.id || q1.id == p2.id || q1.id == q2.id)
    {
        return 0;
    }

    // Find the four orientations needed for general and
    // special cases
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);

    // General case
    if (o1 != o2 && o3 != o4)
    {
        return 1;
    }

    // Special Cases
    // p1, q1 and p2 are colinear and p2 lies on segment p1q1
    if (o1 == 0 && onSegment(p1, p2, q1))
        return 1;

    // p1, q1 and q2 are colinear and q2 lies on segment p1q1
    if (o2 == 0 && onSegment(p1, q2, q1))
        return 1;

    // p2, q2 and p1 are colinear and p1 lies on segment p2q2
    if (o3 == 0 && onSegment(p2, p1, q2))
        return 1;

    // p2, q2 and q1 are colinear and q1 lies on segment p2q2
    if (o4 == 0 && onSegment(p2, q1, q2))
        return 1;

    return 0; // Doesn't fall in any of the above cases
}

int countIntersections(Line line, int n_lines)
{
    int count = 0;
    for (int l = 0; l < n_lines; l++)
    {
        //Without saving
        //int intersection_type = doIntersect(line.source, line.target, lines[i].source, lines[i].target);
        //count += intersection_type;
        //With saving
        int intersection = intersections[lines[l].source.id][lines[l].target.id][line.source.id][line.target.id];
        if (intersection == 0)
        {
            intersection = doIntersect(line.source, line.target, lines[l].source, lines[l].target);
            if (intersection == 0)
            {
                intersection = 2;
            }
            else
            {
                intersection = 1;
                count++;
            }
            //Save the intersections
            intersections[lines[l].source.id][lines[l].target.id][line.source.id][line.target.id] = intersection;
            intersections[lines[l].source.id][lines[l].target.id][line.target.id][line.source.id] = intersection;
            intersections[lines[l].target.id][lines[l].source.id][line.source.id][line.target.id] = intersection;
            intersections[lines[l].target.id][lines[l].source.id][line.target.id][line.source.id] = intersection;

            intersections[line.source.id][line.target.id][lines[l].source.id][lines[l].target.id] = intersection;
            intersections[line.target.id][line.source.id][lines[l].source.id][lines[l].target.id] = intersection;
            intersections[line.source.id][line.target.id][lines[l].target.id][lines[l].source.id] = intersection;
            intersections[line.target.id][line.source.id][lines[l].target.id][lines[l].source.id] = intersection;
        }
        else if (intersection == 2)
        {
            continue;
        }
        else
        {
            count++;
        }
    }
    return count;
}

void recursive(int device_atual, int num_intersections, int n_lines)
{

    /*    printf("-> %d %d %d\n", device_atual, num_intersections, n_lines);
    for (int i = 0; i < n_lines; i++){
        cout << "Line between coordinates " << lines[i].source.id << " and " << lines[i].target.id << endl;
    }*/

    if (num_intersections >= best_case)
    {
        return;
    }

    //If all placed
    if (device_atual > n_devices)
    {
        best_case = num_intersections;
        return;
    }

    //Search the next device
    int next_device = device_atual + 1;
    for (int device = device_atual + 1; device <= n_devices; ++device)
    {
        if (device_to_use[device] == true)
        {
            next_device = device;
            break;
        }
    }

    for (int coordinate = 1; coordinate <= n_coordinates; coordinate++)
    {
        if (coordinates_used[coordinate] == false)
        {
            //cout << "Device " << device_atual << " in coordinate " << coordinate << endl;
            device_placed[device_atual] = coordinate;
            coordinates_used[coordinate] = true;

            int count_intersections = 0;
            int n_lines_new = n_lines;
            for (int adjacent = 0; adjacent < (int)adjacencies[device_atual].size(); adjacent++)
            {
                int adjacent_device = adjacencies[device_atual][adjacent];
                if (device_placed[adjacent_device] != 0)
                {
                    //Create line
                    Line new_collider;
                    new_collider.source = coordinates[device_placed[device_atual]];
                    new_collider.target = coordinates[device_placed[adjacent_device]];
                    count_intersections += countIntersections(new_collider, n_lines);
                    lines[n_lines_new] = new_collider;
                    n_lines_new++;
                }
            }

            recursive(next_device, num_intersections + count_intersections, n_lines_new);

            device_placed[device_atual] = 0;
            coordinates_used[coordinate] = false;
        }
    }
}

int main()
{

    cin >> n_coordinates;

    for (int i = 1; i <= n_coordinates; i++)
    {
        Point p;
        cin >> p.x >> p.y;
        p.id = i;
        coordinates[i] = p;
    }

    cin >> n_devices >> n_colliders;

    for (int i = 1; i <= n_colliders; i++)
    {
        int source, target;
        cin >> source >> target;
        device_to_use[source] = device_to_use[target] = true;
        adjacencies[source].push_back(target);
        adjacencies[target].push_back(source);
    }

    n_devices_to_place = 0;
    for (int i = 1; i <= n_devices; i++)
    {
        if (device_to_use[i] == true)
        {
            n_devices_to_place++;
        }
    }

    best_case = 99999999;

    //Get the first device
    int first_device;
    for (int device = 1; device <= n_devices; ++device)
    {
        if (device_to_use[device] == true)
        {
            first_device = device;
            break;
        }
    }

    //Get the second device
    int second_device;
    for (int device = first_device + 1; device <= n_devices; ++device)
    {
        if (device_to_use[device] == true)
        {
            second_device = device;
            break;
        }
    }

    for (int coordinate = 1; coordinate <= n_coordinates; coordinate++)
    {
        coordinates_used[coordinate] = true;
        device_placed[first_device] = coordinate;
        recursive(second_device, 0, 0);
        device_placed[first_device] = 0;
        coordinates_used[coordinate] = false;
    }

    cout << best_case << endl;

    return 0;
}