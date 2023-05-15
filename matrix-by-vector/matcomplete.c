//Parallel algorithm for calculating matrix product by vector using reduction and second strategy
#include <math.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

//numero divisibile per 12
#define SIZE 600

int main(){
    
    //variabili per segnare i tempi
    double t0, t1;

    double A[SIZE][SIZE];
    double x[SIZE];
    double B[SIZE];

    for(int i = 0; i<SIZE; i++){
        for(int j = 0; j<SIZE; j++){
            A[i][j] = i*SIZE+j;
        }
        x[i] = i;
    }   

    t0 = omp_get_wtime();

    #pragma omp parallel for default(none) shared(A,x,B)
    for(int i = 0; i<SIZE; i++){
        for(int j = 0; j<SIZE; j++){
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