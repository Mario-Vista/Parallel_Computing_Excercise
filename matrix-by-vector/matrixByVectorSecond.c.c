//Parallel algorithm for calculating matrix product by vector using rectangular matrix and second strategy
/* Using second strategy for the matrix product by vector means dividing the matrix in column block,
using each vector cell as a row vector, and calculating the row by column product for each block.

Time analysis:
0.004 with size = 960 and 12 thread
0.003 with size = 600 and 1 thread
0.001 with size = 600 and 12 thread
*/

#include <math.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

//size should be set to a number divisible by 12(number of core of my computer)
#define SIZE 600

int main(){
    
    //variables to track execution time
    double t0, t1;
    
    //matrix static declaration
    double A[SIZE][SIZE];
    
    //vector static declaration
    double x[SIZE];

    //resultant vector declaration
    double B[SIZE];


    //initialization of matrix using memory map
    for(int i = 0; i<SIZE; i++){
        for(int j = 0; j<SIZE; j++){
            A[i][j] = i*SIZE+j;
        }
        //initialization of vector
        x[i] = i;
    }   

    //track time before the begin of parallel section
    t0 = omp_get_wtime();

    //begin of parallel section
    #pragma omp parallel for default(none) shared(A,x,B)
    //distributed for
    for(int i = 0; i<SIZE; i++){
        for(int j = 0; j<SIZE; j++){
            //A use j(not distributed index) for rows and i(distributed index) for column
            //B use i(distributed index) to avoid race condition during parallel result asignment
            //x use j(not distributed index)
            B[i]+=A[j][i]*x[j];

        }
    }
    //ed of parallel section


    //track time after the end of parallel section
	t1 = omp_get_wtime();

    //print of total time
    printf("Total time: %lf\n", t1-t0);

}
