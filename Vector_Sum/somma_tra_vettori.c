//somma tra due vettori in cui il numero di elementi è divisibile per il numero di core utilizzati
//provato su due thread  e 4 numeri per array

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	//t= numero di thread con cui voglio lavorare
	//nloc = numero di elementi locali di cui si dovrà occupare il singolo thread
	int i, N, t, nloc, indice;
	float *a,*b,*c;

	printf("inserire N\n");
	scanf("%d", &N);

	//allocazione
	a=(float*)calloc(N,sizeof(float));
	b=(float*)calloc(N,sizeof(float));
	c=(float*)calloc(N,sizeof(float));

	//lettura
	printf("Inserire gli elementi del vettore a: \n");

	for(i=0; i<N; i++){
		scanf("%f", &a[i]);
	}

	printf("Inserire gli elementi del vettore b: \n");
	
	for(i=0; i<N; i++){
		scanf("%f", &b[i]);
	}

	//inizio della parte parallela
	#pragma omp parallel private(nloc, i, indice, t), shared (a,b,c)
	{ 
		t = omp_get_num_threads();
		nloc=N/t;
		printf("sono il core %d, di %d: numeri di elementi di cui mi occupo %d\n", omp_get_thread_num(), t, nloc);

		for(i=0; i<nloc; i++){
			 indice = i+nloc*omp_get_thread_num();
			c[indice] = a[indice] +b[indice];
		}


		for(i=0; i<N; i++){
			printf(" %f ", c[i]);
		}

	}

}