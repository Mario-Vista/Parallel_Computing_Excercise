//somma tra due vettori in cui il numero di elementi NON è divisibile per il numero di core utilizzati
//testato con N=6 e 4 core: export OMP_NUM_THREADS=4

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	//t= numero di thread con cui voglio lavorare
	//nloc = numero di elementi locali di cui si dovrà occupare il singolo thread
	//r = resto
	//step = scprrere gli elementi

	int i, N, t, nloc, indice, r, id, step;
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
	#pragma omp parallel private(nloc, i, indice, t, id, step), shared (a,b,c, r)
	{ 
		t = omp_get_num_threads();
		nloc=N/t;
		r= N%t;
		id = omp_get_thread_num();

		printf("sono il core %d, di %d: numeri di elementi di cui mi occupo %d, resto = %d\n", id, t, nloc, r);

		//suddivisione del lavoro fra i vari thread
		if(id<r){
			nloc++;
			step=0;
		} else {
			step = r;
		}

		printf("sono il core %d, di %d: numeri di elementi di cui mi occupo %d, resto = %d , passo = %d\n", id, t, nloc, r, step);


		for(i=0; i<nloc; i++){
			 indice = i+nloc*omp_get_thread_num()+step;
			c[indice] = a[indice] +b[indice];
		}


		for(i=0; i<N; i++){
			printf(" %f ", c[i]);
		}

	}

}