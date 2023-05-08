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
	float sumtot,sum,*a;
	sumtot = 0;

	printf("inserire N\n");
	scanf("%d", &N);

	//allocazione
	a=(float*)calloc(N,sizeof(float));


	//lettura
	printf("Inserire i numeri da sommare: \n");

	for(i=0; i<N; i++){
		scanf("%f", &a[i]);
	}


	//inizio della parte parallela
	#pragma omp parallel private(nloc, i, indice, t, id,sum, step), shared (sumtot, r)
	{ 
		t = omp_get_num_threads();
		nloc=N/t;
		r= N%t;
		id = omp_get_thread_num();

		//suddivisione del lavoro fra i vari thread
		if(id<r){
			nloc++;
			step=0;
		} else {
			step = r;
		}



		for(i=0; i<nloc; i++){
			 sum = sum+a[i+nloc*omp_get_thread_num()+step];
		}
		printf("sono il core %d, di %d: numeri di elementi di cui mi occupo %d,resto= %d miasu= %f\n", id, t, nloc, r, sum);
		sumtot+=sum;
		}

		printf("la somma dei numeri è: %f\n", sumtot);

	}