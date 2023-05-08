//corretto ma i thread sono in contesa
#include <stdio.h>
#include <omp.h>
#define N 100000000

int main(int argc, char **argv)
{
	long int i, n=N;
	double x, dx, f, sum, pi;

	printf("numero di intervalli: %ld\n", n);
	sum = 0.0;

	dx = 1.0/(double)n;

	//cafonata
	//forza il sequenziale ossia la scrittura all'interno della direttiva in modo che ogni thread scriva uno alla volta in un certo ordine
	#pragma omp parallel for private(x,f,i) shared(dx,sum,n)
	for(i = 1; i<=n; i++){

		x = dx * ((double)(i-0.5));
		f=4.0/(1.0+x*x);
		
		#pragma omp critical
		//cafonata
		//forza il sequenziale ossia la scrittura all'interno della direttiva in modo che ogni thread scriva uno alla volta in un certo ordine
		sum = sum +f;
	}

	pi = dx*sum;

	printf("PI %.24f\n", pi);


	return 0;
}