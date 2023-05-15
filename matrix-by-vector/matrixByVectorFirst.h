//Parallel algorithm for calculating matrix product by vector using reduction and first strategy
#include <math.h>
#include <omp.h>
#include <stdlib.h>

double * matxvet(int m, int n, double *x, double **A){
    int i, j;
    double *b;

    //allocazione memoria b

    #pragma omp parallel for default(none) shared(m,n,A,x,b) private(i,j)
    for(i = 0; i<n; i++){
        for(j = 0; j<m; j++){
            b[i]+=A[i][j]*x[j];
        }
        //fine del parallelo
    }
    return b;

}