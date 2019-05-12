#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <cstring>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

int n_test_cases;


int main(){
    cin>>n_test_cases;
    cout<<n_test_cases<<endl;
    for(int i=0;i<n_test_cases;i++){
        int n_enxames=0, n_tecnicos=0, distance_z=0, distance_w=0;
        cin>>n_enxames>>n_tecnicos>>distance_z>>distance_w;
        cout<<n_enxames<<" "<<n_tecnicos<<" "<<distance_z<<" "<<distance_w<<endl;
        for (int m=0;m<n_tecnicos;m++){
            int x=0,y=0;
            cin>>x>>y;
            cout<<x<<" "<<y<<endl;
        }
        for(int n=0;n<n_enxames;n++){
            int n_robots=0;
            cin>>n_robots;
            cout<<n_robots<<endl;

            for(int r=0;r<n_robots;r++){
                int x_robot=0,y_robot=0;
                cin>>x_robot>>y_robot;
                cout<<x_robot<<" "<<y_robot<<endl;
            }

        }
    }
}