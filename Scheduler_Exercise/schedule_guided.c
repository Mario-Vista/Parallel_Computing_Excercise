#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include<unistd.h>
#include<omp.h>

#define N 10000
#define CHUNK 4

/*CHUNCK assegna il numero di iterazioni ad ogni singolo thread, con 4 ha tempi migliori rispetto a se lo impostazzimo a 10 o 20, con 20 ad esempio è molto più alto  schedule(dynamic,CHUNK)*/

/*schedule(static) esegue Round Roubin
schedule(dynamic) esegue FCFS*/

int main()
{
	int n_threads, id_thread, i;
	double t1;
	double t2;
	int sumtot = 0, *a, sum, t, nloc;
	
	
	//Allocazione
	a = (int *)calloc(N, sizeof(int));
	
	
	//Lettura
	printf("Inserire gli elementi da sommare: \n");
	for(i = 0; i < N; i++)
	{
		a[i] = i+1;
	}
	
	//omp_set_num_threads(3);
	t1 = omp_get_wtime();
	printf("\nStampa t1: %f", t1);
	
	sum = 0;
	#pragma omp parallel for private(i,sum)shared(sumtot)schedule(guided)num_threads(4)
		for(i = 0; i < N; i++)
		{
		
			sum = a[i];
			printf("Il thread %d ha completato l'iterazione %d \n", omp_get_thread_num(), i);
			#pragma omp atomic
			sumtot += sum;
		}
		
		
		
	t2 = omp_get_wtime();
	printf("\nStampa t2: %f", t2);
	
	printf("\nTempo finale: %f", t2-t1);
	printf("\nSomma: %d",sumtot);
	printf("\nTutti i thread hanno terminato\n");

return 0;

}