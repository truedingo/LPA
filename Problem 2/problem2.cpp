#include <iostream>
#include <vector>
#include <algorithm>

#define MAX_EVENTS 10000

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



int maximumProfit(){

    int max_deadline = events[n_events-1][0];       // vai buscar a maior deadline
    vector <vector<int> > events_table(n_events+1,vector<int>(max_deadline+1,-1)); //inicializa a matriz com -1
                                                     //as linhas são eventos e as colunas é o t até à   
                                                                     //maior deadline
    for (int t = 0; t <= max_deadline; t++){
        events_table[0][t] = 0;             //incializa a primeira linha a zero
    }
    
    
    for (int i=1; i <=n_events; i++){
        for (int t = 0; t<= max_deadline; t++){
            int new_T  = min(t,events[i-1][0]) - events[i-1][1];    //vai ver qual é o t minimo  e subtrai a esse valor, a duração do evento
            if (new_T < 0){
                events_table[i][t] = events_table[i-1][t]; //se o novo valor de t for menos que zero, a matriz é atualizada 
                                                            // com o valor da linha anterior
            }
            else{
                events_table[i][t] = max(events_table[i-1][t],events[i-1][2]+ events_table[i-1][new_T]);
                //caso contrário, guarda o maior lucro entre o valor anterior e o o lucro do evento i-1 + o 
                //valor que está na linha i-1 , na coluna do novo valor de t.

            }
        
        }
       
    }
    return events_table[n_events][max_deadline];
}

int main(){
    cin>>n_events;

    for(int event=0;event<n_events;event++){
        cin>> events[event][0]>>events[event][1]>>events[event][2];
    }
    quickSort(0,n_events-1);  //ordenar os eventos por deadline, de forma crescente
    
    cout<<maximumProfit()<<endl;
    return 0;
}
