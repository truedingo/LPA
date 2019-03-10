#include <iostream>
#include <vector>

#define MAX_COORDINATES 81
#define MAX_DEVICES 81
#define MAX_COLLIDERS 28

using namespace std;

int n_coordinates;
int n_devices, n_real_devices;
int n_colliders;
int best_case;

int coordinates[MAX_COORDINATES][3]; // [0] is x , [1] is y, [2] is id
bool coordinate_used[MAX_COORDINATES];
int place_of_device[MAX_COORDINATES];
int real_devices[MAX_DEVICES];
bool device_to_use[MAX_DEVICES];
int intersections_saved[MAX_DEVICES][MAX_DEVICES][MAX_DEVICES][MAX_DEVICES];
int lines[MAX_COLLIDERS][2]; // [0] is source , [1] is target
vector<int> adjacencies[MAX_DEVICES]; 

//just to print the best solutions for validation
int place_of_device_best[MAX_COORDINATES];
int lines_best[MAX_COLLIDERS][2];

void printCoordinates()
{
    int i;
    cout << "Coordinates vector: " << endl;
    cout << " " << endl;

    for (i = 1; i <= n_coordinates; i++)
    {
        cout << "X: " << coordinates[i][0] << " Y: " << coordinates[i][1] << endl;
    }

    cout << " " << endl;
    cout << "End of Coordinates vector" << endl;
    cout << endl;
}

void print_coordinate_used()
{
    for (int i = 1; i <= n_coordinates; i++)
    {
        cout << "place " << i + 1 << ": " << coordinate_used[i] << endl;
    }
}

void print_place_of_device()
{
    for (int i = 1; i <= n_coordinates; i++)
    {
        cout << "device: " << i + 1 << "on place: " << place_of_device[i] << endl;
    }
}

void print_best()
{
    for (int i = 1; i <= n_devices; i++)
    {
        cout << "device: " << i << " at place " << place_of_device_best[i] << endl;
    }
}

//--------------------------------------------------------------------------------------------------------------------
// from: https://www.geeksforgeeks.org/check-if-two-given-line-segments-intersect/
// Given three colinear points p, q, r, the function checks if
// point q lies on line segment 'pr'
bool onSegment(int px, int py, int qx, int qy, int rx, int ry)
{
    if (qx <= max(px, rx) && qx >= min(px, rx) &&
        qy <= max(py, ry) && qy >= min(py, ry))
        return true;

    return false;
}

// To find orientation of ordered triplet (p, q, r).
// The function returns following values
// 0 --> p, q and r are colinear
// 1 --> Clockwise
// 2 --> Counterclockwise
int orientation(int px, int py, int qx, int qy, int rx, int ry)
{
    // See https://www.geeksforgeeks.org/orientation-3-ordered-points/
    // for details of below formula.
    int val = (qy - py) * (rx - qx) -
              (qx - px) * (ry - qy);

    if (val == 0)
        return 0; // colinear

    return (val > 0) ? 1 : 2; // clock or counterclock wise
}

// // The main function that returns true if line segment 'p1q1'
// // and 'p2q2' intersect.
int doIntersect(int p1x, int p1y, int q1x, int q1y, int p2x, int p2y, int q2x, int q2y)
{

    // Find the four orientations needed for general and
    // special cases
    int o1 = orientation(p1x, p1y, q1x, q1y, p2x, p2y);
    int o2 = orientation(p1x, p1y, q1x, q1y, q2x, q2y);
    int o3 = orientation(p2x, p2y, q2x, q2y, p1x, p1y);
    int o4 = orientation(p2x, p2y, q2x, q2y, q1x, q1y);

    // General case
    if (o1 != o2 && o3 != o4)
    {
        return 1;
    }

    // Special Cases
    // p1, q1 and p2 are colinear and p2 lies on segment p1q1
    if (o1 == 0 && onSegment(p1x, p1y, p2x, p2y, q1x, q1y))
        return 1;

    // p1, q1 and q2 are colinear and q2 lies on segment p1q1
    if (o2 == 0 && onSegment(p1x, p1y, q2x, q2y, q1x, q1y))
        return 1;

    // p2, q2 and p1 are colinear and p1 lies on segment p2q2
    if (o3 == 0 && onSegment(p2x, p2y, p1x, p1y, q2x, q2y))
        return 1;

    // p2, q2 and q1 are colinear and q1 lies on segment p2q2
    if (o4 == 0 && onSegment(p2x, p2y, q1x, q1y, q2x, q2y))
        return 1;

    return 2; // Doesn't fall in any of the above cases
}

int countIntersections(int source_id, int target_id, int n_lines)
{
    int count = 0;
    for (int l = 0; l < n_lines; l++)
    {
        //Without saving
        //int intersection_type = doIntersect(line.source, line.target, lines[i].source, lines[i].target);
        //count += intersection_type;

        //With saving
        int source_line_id = lines[l][0];
        int target_line_id = lines[l][1];
        int intersection = intersections_saved[source_line_id][target_line_id][source_id][target_id];
        if (intersection == 0)
        {
            //Common point
            if (coordinates[source_id][2] == coordinates[source_line_id][2] || coordinates[source_id][2] == coordinates[target_line_id][2] || coordinates[target_id][2] == coordinates[source_line_id][2] || coordinates[target_id][2] == coordinates[target_line_id][2])
            {
                intersection = 2;
            }
            else
            {
                intersection = doIntersect(coordinates[source_id][0], coordinates[source_id][1], coordinates[target_id][0], coordinates[target_id][1], coordinates[source_line_id][0], coordinates[source_line_id][1], coordinates[target_line_id][0], coordinates[target_line_id][1]);
            }

            if (intersection == 1)
            {
                count++;
            }
            //Save the intersections - all the 8 possibilities 
            intersections_saved[coordinates[source_line_id][2]][coordinates[target_line_id][2]][source_id][target_id] = intersection;
            intersections_saved[coordinates[source_line_id][2]][coordinates[target_line_id][2]][target_id][source_id] = intersection;
            intersections_saved[coordinates[target_line_id][2]][coordinates[source_line_id][2]][source_id][target_id] = intersection;
            intersections_saved[coordinates[target_line_id][2]][coordinates[source_line_id][2]][target_id][source_id] = intersection;

            intersections_saved[source_id][target_id][coordinates[source_line_id][2]][coordinates[target_line_id][2]] = intersection;
            intersections_saved[target_id][source_id][coordinates[source_line_id][2]][coordinates[target_line_id][2]] = intersection;
            intersections_saved[source_id][target_id][coordinates[target_line_id][2]][coordinates[source_line_id][2]] = intersection;
            intersections_saved[target_id][source_id][coordinates[target_line_id][2]][coordinates[source_line_id][2]] = intersection;
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

void recursive(int index_real_device, int num_intersections, int n_lines)
{

    /*    printf("-> %d %d %d\n", device_atual, num_intersections, n_lines);
    for (int i = 0; i < n_lines; i++){
        cout << "Line between coordinates " << lines[i].source.id << " and " << lines[i].target.id << endl;
    }*/

    //if we already have more intersections than our best case
    if (num_intersections >= best_case)
    {
        return;         //o(1)
    }

    //If all placed
    if (index_real_device == n_real_devices)
    {
        //if we found a better best case, we save the best lines, and the places for the devices.
        if (num_intersections < best_case)
        {
            for (int i = 1; i <= n_devices; i++)
            {
                place_of_device_best[i] = place_of_device[i];
                place_of_device_best[i] = place_of_device[i];   //O(N)
                place_of_device_best[i] = place_of_device[i];
            }
            for (int i = 0; i < n_lines; i++)
            {
                lines_best[i][0] = lines[i][0];      //O(N)
                lines_best[i][1] = lines[i][1];
            }
            //save best case
            best_case = num_intersections;
        }
        return;
    }

    //Search the next real (used) device (the devices are not all placed)
    int device_atual = real_devices[index_real_device];

    for (int coordinate = 1; coordinate <= n_coordinates; coordinate++)
    {
        //if the place was not used
        if (coordinate_used[coordinate] == false)
        {
            //now we use the coordinate and associate the device with the coordinate (place)
            place_of_device[device_atual] = coordinate;
            coordinate_used[coordinate] = true;

            int count_intersections = 0;
            bool flag = true;
            int n_lines_new = n_lines;
            //now we look for the adjacencies of the device
            for (int adjacent = 0; adjacent < (int)adjacencies[device_atual].size(); adjacent++)
            {

                int adjacent_device = adjacencies[device_atual][adjacent];
                if (place_of_device[adjacent_device] != 0)
                {
                    //Create line
                    int source_id, target_id;
                    source_id = coordinates[place_of_device[device_atual]][2];
                    target_id = coordinates[place_of_device[adjacent_device]][2];
                    count_intersections += countIntersections(source_id, target_id, n_lines);

                    //if we are going to have a bigger number to best case, we dont try this place
                    if (num_intersections + count_intersections >= best_case)
                    {
                        flag = false;                                                               
                        break;
                    }

                    lines[n_lines_new][0] = source_id;
                    lines[n_lines_new][1] = target_id;
                    n_lines_new++;
                }
            }

            // if num_intersections + count_intersections < best_case
            if (flag == true)
            {
                recursive(index_real_device + 1, num_intersections + count_intersections, n_lines_new);
            }

            place_of_device[device_atual] = 0;
            coordinate_used[coordinate] = false;
            flag = true;
        }
    }
}

int main()
{

    cin >> n_coordinates;

    for (int i = 1; i <= n_coordinates; i++)
    {
        int x, y;
        cin >> x >> y;
        coordinates[i][0] = x;
        coordinates[i][1] = y;
        coordinates[i][2] = i;
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

    n_real_devices = 0;
    //devices that are actually used
    for (int i = 1; i <= n_devices; i++)
    {
        if (device_to_use[i] == true)
        {
            real_devices[n_real_devices] = i;
            n_real_devices++;
        }
    }

    //Without bound
    best_case = 99999999;

    for (int coordinate = 1; coordinate <= n_coordinates; coordinate++)
    {
        coordinate_used[coordinate] = true;
        //placing the first device
        place_of_device[real_devices[0]] = coordinate;
        //index_real_device = 1 , num_intersections -> ainda so ha um device placed por isso 0, 0 linhas.
        recursive(1, 0, 0);
        place_of_device[real_devices[0]] = 0;
        coordinate_used[coordinate] = false;
    }

    cout << best_case << endl;
    //print_best();

    return 0;
}
