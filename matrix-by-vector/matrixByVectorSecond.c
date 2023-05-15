//Parallel algorithm for calculating matrix product by vector using reduction and second strategy
#include <math.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

/*
double * matxvet(int m, int n, double *x, double **A){
    int i, j;
    double *b;

    //allocazione memoria b

    #pragma omp parallel for default(none) shared(m,n,A,x,b) private(i,j)
    for(i = 0; i<m; i++){
        for(j = 0; j<n; j++){
            b[i]+=A[j][i]*x[j];

        }
        //fine del parallelo
    }
    return b;

}*/


int main(){

    double A[12][12];
    double x[12] = {1,2,3,4,5,6,7,8,9,10,11,12};
    double B[12];

    for(int i = 0; i<12; i++){
        for(int j = 0; j<12; j++){
            A[i][j] = i*12+j;
        }
    }   


    #pragma omp parallel for default(none) shared(m,n,A,x,b) private(i,j)
    for(int i = 0; i<12; i++){
        for(int j = 0; j<12; j++){
            B[i]+=A[j][i]*x[j];

        }
        //fine del parallelo
    }

    
    for(int i = 0; i < 12; i++){
        printf("%lf\n", B[i]);
    }
}