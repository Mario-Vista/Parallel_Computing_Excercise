//Esercizio per il calcolo del prodotto scalare

/*
    Tempi rilevati con i vari schedule sul prodotto scalare dei numeri da 0 a 999:
    dynamic(CHUNCK = 10): 0.000660s;
    static: 0.002180s;
    guided: 0.001023s;
    Si può notare dunque che in queste condizioni lo schedule dynamic risulta nettamente più efficiente.
*/

#include <stdio.h>
#include <omp.h>
#include <time.h>
#include <stdlib.h>
#define CHUNCK 10




int main(){

    //numero di elementi su cui calcolare il prodotto scalare
    int numElem;

    //variante se si vuole calcolare il prodotto scalare di numeri randomici
    //srand(time(NULL));

    //variabili utili per il calcolo
	int a[numElem],b[numElem];
    int storeTimes[numElem];
    int prodottoScalare = 0;
    
    //variabili per segnare i tempi
    double t0, t1;
	double tempoTot;

    printf("inserisci numero di elementi di cui calcolare il prodotto scalare: \n");
    scanf("%d", &numElem);

    /*
        //variante se si vuole calcolare il prodotto scalare di numeri randomici

        for(int i = 0; i<numElem; i++){
            a[i] = rand();
            b[i] = rand();
        }
    */

    //assegno i valori agli elementi dei due array
    for(int i = 0; i<numElem; i++){
        a[i] = i;
        b[i] = i;
    }
    
    //segno il tempo prima della sezione parallela
    t0 = omp_get_wtime();

    //sezione parallela
   	#pragma omp parallel for schedule(dynamic, CHUNCK)
    for(int i=0; i < numElem; i++){
        //effettuo le moltiplicazioni
        storeTimes[i] = a[i]*b[i];

        //forzo il sequenziale
        #pragma omp atomic
        //aggiorno la somma in modo da ottenere(alla fine del for) il risultato del prodotto scalare
        prodottoScalare = prodottoScalare + storeTimes[i];
    }

    //segno il tempo alla fine della sezione parallela
	t1 = omp_get_wtime();

    //calcolo il tempo totale
	tempoTot = t1-t0;

    printf("Il risultato è: %d\n", prodottoScalare);

    printf("Tempo totale: %lf", tempoTot);

    return 0;


}