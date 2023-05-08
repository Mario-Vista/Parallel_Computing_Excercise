//Odd Even Sort parallel algorithm
#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

#define CHUNK 10

int oddEvenSort(int a[], int N){
    int sw = 1, start = 0, i = 0;
    int temp;

    //using two different flag avoid race condition
    while (sw || start){
        sw = 0;

        #pragma omp parallel for private(temp) shared(sw, start) schedule(dynamic, CHUNK)
        for(int i = start; i<N-1; i+=2){
            if(a[i] > a[i+1])
            {
                temp = a[i];
                a[i] = a[i+1];
                a[i+1] = temp;
                sw = 1;
            }
        }
        if(start == 0){
            start = 1;
        } else 
            start = 0;

    } 


}