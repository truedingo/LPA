#include <iostream>
#include <stdio.h>
#include <vector>

#define MAX_EVENTS 10000
#define LARGEST_DEADLINE 100000

using namespace std;

int n_events;
int events[MAX_EVENTS][3];


// A utility function to swap two elements 
void swap(int* a, int* b) 
{ 
    int t = *a; 
    *a = *b; 
    *b = t; 
} 

/* This function takes last element as pivot, places 
   the pivot element at its correct position in sorted 
    array, and places all smaller (smaller than pivot) 
   to left of pivot and all greater elements to right 
   of pivot */
int partition (int low, int high) 
{ 
    int pivot = events[high][0];    // pivot 
    int i = (low - 1);  // Index of smaller element 
  
    for (int j = low; j <= high- 1; j++) 
    { 
        // If current element is smaller than or 
        // equal to pivot 
        if (events[j][0] <= pivot) 
        { 
            i++;    // increment index of smaller element 
            swap(events[i][0], events[j][0]);
            swap(events[i][1], events[j][1]);  
            swap(events[i][2], events[j][2]);  
        } 
    } 
    swap(events[i + 1][0], events[high][0]); 
    swap(events[i + 1][1], events[high][1]); 
    swap(events[i + 1][2], events[high][2]); 

    return (i + 1); 
} 
  
/* The main function that implements QuickSort 
 arr[] --> Array to be sorted, 
  low  --> Starting index, 
  high  --> Ending index */
void quickSort( int low, int high) 
{ 
    if (low < high) 
    { 
        /* pi is partitioning index, arr[p] is now 
           at right place */
        int pi = partition( low, high); 
  
        // Separately sort elements before 
        // partition and after partition 
        quickSort( low, pi - 1); 
        quickSort( pi + 1, high); 
    } 
} 


int main(){

    cin>>n_events;

    for(int event=0;event<n_events;event++){
        cin>> events[event][0]>>events[event][1]>>events[event][2];
    }

    quickSort(0,n_events-1);

    cout<<"Number of Events: "<<n_events<<endl;

    for(int event=0;event<n_events;event++){
        cout << "Deadline: " << events[event][0]<< " Duration: " <<events[event][1] << " Cost: " <<events[event][2] << endl;
    }


    return 0;
}