//Parallel algorithm for calculating matrix product by vector using rectangular matrix and second strategy
#include <math.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

//numero divisibile per 12
#define SIZE2 600
#define SIZE 960

int main(){

    //variabili per segnare i tempi
    double t0, t1;

    double A[SIZE][SIZE2];
    double x[SIZE2];
    double B[SIZE];

    for(int i = 0; i<SIZE; i++){
        for(int j = 0; j<SIZE2; j++){
            A[i][j] = i*SIZE2+j;
        }
        
    }   

    for(int i = 0; i<SIZE2; i++){
        x[i] = i;
    }

    t0 = omp_get_wtime();

    #pragma omp parallel for default(none) shared(A,x,B)
    for(int i = 0; i<SIZE; i++){
        for(int j = 0; j<SIZE2; j++){
            B[i]+=A[j][i]*x[j];

        }
        //fine del parallelo
    }

        //segno il tempo alla fine della sezione parallela
	t1 = omp_get_wtime();


    printf("tempo totale: %lf\n", t1-t0);

}

//0.004 960
//0.003 600