#include <stdio.h>
#include <stdlib.h>

int n_functions = 0;



int check_recursive(int arr [n_functions][n_functions], int id, int * visited, int initial) {
    int i;

    if(visited[id] == 1 && id == initial) return 1;
    else if(visited[id] == 1 && id != initial) return 0;
    

    visited[id] = 1;
   
    
    for(i = 0; i < n_functions; i++) {
        if(arr[id][i] == 1) {
            if(check_recursive(arr, i, visited, initial)) return 1;
        }
    }
    
    return 0;
}



int main() {


    int i, n_reads, j;
    int aux;

    scanf("%d\n", &n_functions);
    int arr [n_functions][n_functions];

 
    /*init array*/
    for (i = 0; i < n_functions; i++) {
        for( j = 0; j < n_functions; j++) {
            arr[i][j] = 0;
        }
    }


    for(i = 0; i < n_functions; i++) {
        
        scanf("%d",&n_reads);
  

        while (n_reads > 0) {
            scanf("%d",&aux);
            arr[i][aux] = 1;
            n_reads--;
        }

    }
    /*
    for (i = 0; i < n_functions; i++) {
        for(ii = 0; ii < n_functions; ii++) {
            printf("%d ", arr[i][ii]);
        }
        printf("\n");
    }*/

    

    for(i = 0; i < n_functions; i++) {
        int * visited = calloc(n_functions, sizeof(int));
        
        if(check_recursive(arr, i, visited, i)) {
            printf("%d\n", i);
        }

    }

    


    return 0;
}