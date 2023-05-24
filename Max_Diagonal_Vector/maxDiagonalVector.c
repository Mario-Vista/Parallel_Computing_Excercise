//Parallel algorithm for calculating the max element in a diagonal matrix

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <omp.h>

//Matrix size
#define n 3

int main()
{

	int **matrix;
	int *diag;

	//Matrix allocation
	matrix = (int**) calloc(n,sizeof(int*));
	diag = (int*) calloc(n,sizeof(int));

	for(int i = 0; i < n; i++)
	{
		matrix[i] = (int*) calloc(n,sizeof(int));
	}
	
	
	//Matrix filling
	for(int i = 0; i < n; i++)
	{
		for(int j = 0 ; j < n ; j++)
		{
				matrix[i][j] = i + j;
		}
	}
	
	printf("\nPrint the matrix:\n");
	for(int i = 0; i< n; i++)
	{
		for(int j = 0; j < n; j++)
		{
			printf("%d ", matrix[i][j]);
		}
		printf("\n");
	}
	
	
	//Calculate and saving diagonal matrix
	#pragma omp parallel for shared(matrix,diag) num_threads(2)
		for(int i = 0; i < n; i++)
		{
			diag[i] = matrix[i][i];
		}
	
	printf("\nPrint the diagonal:\n");
	for(int i = 0 ; i < n; i ++)
	{
			printf(" %d \n",diag[i]);
	}

	int max_value = diag[0];
	
	//Calculate the maximum element of the diagonal
	#pragma omp parallel for shared(diag) reduction(max: max_value) num_threads(2)
		for(int i = 1 ; i < n ; i++)
		{
			if(diag[i] > max_value)
			{
				max_value = diag[i];
			}
		}
	
	printf("\nMassimo valore del vettore diagonale: %d\n", max_value);

	return 0;
}

