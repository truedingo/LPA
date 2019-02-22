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
        cout << "x: " << coordinates[i].x << " y: " << coordinates[i].y << endl;
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
        cout << "Source: " << pairs[i].source << " Target: " << pairs[i].target << endl;
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
        }
    }

    return 0;
}