
#include <cstdlib>
#include <iostream>
#include <utility>
#include <vector>
#include <string>
using namespace std;
int minimo = -1;
int c = 0;
int n_div;
  
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


void recursiva(int div, int escolhidos[][2], int lista[], int size, int atual, int n_places, vector<pair<int,int> > places, vector<pair<int,int> > ligacoes){
	if (atual == n_places)
		return;

	if (div != -1){
		escolhidos[div][0] = places[atual].first;
		escolhidos[div][1] = places[atual].second;
		size++;
	}

	if (size == n_div) {
		c++;
		int mini = 0;
		for (int i = 0; i < ligacoes.size(); ++i)
		{
			/* code */
			for (int j = i + 1; j < ligacoes.size(); ++j){
				Point p1, p2, p3, p4;
				p1.x = escolhidos[ligacoes[i].first][0];
				p1.y = escolhidos[ligacoes[i].first][1];
				p2.x = escolhidos[ligacoes[i].second][0];
				p2.y = escolhidos[ligacoes[i].second][1];
				p3.x = escolhidos[ligacoes[j].first][0];
				p3.y = escolhidos[ligacoes[j].first][1];
				p4.x = escolhidos[ligacoes[j].second][0];
				p4.y = escolhidos[ligacoes[j].second][1];
				
				if (doIntersect(p1, p2, p3, p4)){
					mini++;
				}
			}
		}

		if (minimo == -1 || mini < minimo){		
			cout << "->" << mini<< endl;
			for (int i = 0; i < n_div; i++){
				cout << escolhidos[i][0] << ", " << escolhidos[i][1] << endl;
			}


			minimo = mini;
		}
		return;
	}

	for (int i = 0; i < n_div; i++){
		if (lista[i] == 1){
			lista[i] = 0;
			recursiva(i , escolhidos, lista, size, atual+1, n_places, places, ligacoes);
			lista[i] = 1;
		}
	}
	recursiva(-1 , escolhidos, lista, size, atual+1, n_places, places, ligacoes);

	return;
}

int main(){
	int n_places;
	int a,b;
	int n_lig;
	vector<pair<int,int> > places;
	vector<pair<int,int> > ligacoes;
	
	cin >> n_places;

	for (int i = 0; i < n_places; i++){
		cin >> a >> b;
		places.push_back(make_pair(a,b));
	}

	cin >> n_div >> n_lig;
	int escolhidos[81][2];
	int lista[81];

	for (int i = 0; i < n_div; i++){
		lista[i] = 1;
	}

	for (int i = 0; i < n_lig; i++){
		
		cin >> a >> b;
		ligacoes.push_back(make_pair(a,b));
	}

	for (int i = 0; i < places.size(); ++i)
	{
		cout << places[i].first << " " << places[i].second << "\n";
	}

	for (int i = 0; i < n_div; i++){
		lista[i] = 0;
		recursiva(i , escolhidos, lista, 0, 0, n_places, places, ligacoes);
		lista[i] = 1;
	}
	recursiva(-1 , escolhidos, lista, 0, 0, n_places, places, ligacoes);

	cout << minimo << "\n";
	cout << c << "\n";
	return 0;
}