#include <iostream>
#include <vector>

#define MAX_EVENTS 10000
#define LARGEST_DEADLINE 100000

using namespace std;

int n_events;


int events[MAX_EVENTS][3];

int main(){

    cin>>n_events;

    for(int event=0;event<n_events;event++){
        cin>> events[event][0]>>events[event][1]>>events[event][2];
    }

    cout<<"Number of Events: "<<n_events<<endl;

    for(int event=0;event<n_events;event++){
        cout << "Deadline: " << events[event][0]<< " Duration: " <<events[event][1] << " Cost: " <<events[event][2] << endl;
    }


    return 0;
}