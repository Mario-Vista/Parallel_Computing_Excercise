#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include<unistd.h>
#include<omp.h>


#define N 4

int main(){

	int n_threads, id_thread, i;
	int *a, *b , *c, prodscalar = 0, sum;
	double t1;
	double t2;
	
	
	//Allocazione di a
	a = (int *)calloc(N, sizeof(int));
	
	//Allocazione di b
	b = (int *)calloc(N, sizeof(int));
	
	//Allocazione di c
	c = (int *)calloc(N, sizeof(int));
	
	
	//lettura
	printf("Inserire gli elementi del vettore a\n");
	for(i = 0; i < N; i++)
	{
		scanf("%d", &a[i]);
	}
	printf("Inserire gli elementi del vettore b\n");
	for(i = 0; i < N; i++)
	{
		scanf("%d", &b[i]);
	}
	
	//inizializzo c
	for(i = 0; i < N; i++)
	{
		c[i] = 0;
	}

	
	//Tempo iniziale 
	t1 = omp_get_wtime();
	
	//Prodotto Scalare di due vettori
	#pragma omp parallel for private(i)shared(a,b,c)schedule(static)num_threads(4)
		for(i = 0; i < N; i++)
		{
			c[i] = a[i] * b[i];
			
		}
		
	sum = 0;
	#pragma omp parallel for private(sum)shared(prodscalar)schedule(static)num_threads(4)
		for (i = 0; i < N; i ++)
		{
			sum = c[i];
			
			#pragma omp atomic
			prodscalar += sum;	
		}
		
	
	t2 = omp_get_wtime();
	
	printf("\nTempo finale: %lf", t2-t1);
	
	printf("\nProdotto Scalare: %d",prodscalar);
	printf("\nTutti i thread hanno terminato\n");
	

	return 0;
}