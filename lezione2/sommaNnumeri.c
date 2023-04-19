//algoritmo parallelo per la somma di N numeri utilizzando la prima strategia
//N = 4 thread = 2

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{

	//l'inizializzazione è sequenziale, ci lavora un solo thread

	//t= numero di thread con cui voglio lavorare
	//nloc = numero di elementi locali di cui si dovrà occupare il singolo thread
	//N = numero di elementi da sommare
	int i, N, t, nloc;

	//sumtot = somme totali
	//sum = somme parziali
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
	//il costrutto parallel dice a diversi thread di fare le stesse operazioni su dati diversi

	#pragma omp parallel private(nloc, i, sum), shared (sumtot)
	{ 
		t = omp_get_num_threads();
		nloc=N/t;
		printf("sono il core %d, di %d: numeri di elementi di cui mi occupo %d\n", omp_get_thread_num(), t, nloc);

		for(i=0; i<nloc; i++){
			 sum = sum+a[i+nloc*omp_get_thread_num()];
		}
		sumtot+=sum;
		}

		printf("la somma dei numeri è: %f\n", sumtot);

	}

