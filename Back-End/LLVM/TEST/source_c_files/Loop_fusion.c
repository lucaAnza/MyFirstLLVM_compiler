#include <stdio.h>


void execute2Loop(int **a, int **b , int **c , int **d , int N){

    //Loop0
    for(int i=0 ; i<N ; i++)
        for(int j=0; j<N ; j++)
            a[i][j] = 1/b[i][j] * c[i][j];
    //Loop1
    for(int i=0 ; i<N ; i++)
        for(int j=0; j<N ; j++)
            d[i][j] = a[i][j] * c[i][j];


}

int main() {
    
    int N = 10;
    int **a;
    int **b;
    int **c;
    int **d;

    execute2Loop(a , b , c , d , N);

    return 0;
}


