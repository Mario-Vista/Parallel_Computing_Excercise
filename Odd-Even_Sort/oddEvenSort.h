/* Odd Even Sort parallel algorithm
Odd-Even Sort is a sorting algorith based on Bubble Sort
It functions by comparing all odd/even indexed pairs of adjacent elements in the list and,
if a pair is in the wrong order (the first is larger than the second) the elements are switched.
The next step repeats this for even/odd indexed pairs (of adjacent elements). 
Then it alternates between odd/even and even/odd steps until the list is sorted.
Usually parallel algorithm are not used for comparing operation but this is for an academic exercise*/

#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

#define CHUNK 10

int oddEvenSort(int a[], int N){
    int sw = 1, start = 0, i = 0;
    int temp;

    //using two different flag avoid race condition.
    //If you want to use a single flag you have to manually manage the eventual race condition.
    while (sw || start){
        sw = 0;

        //In this case we use parallel for costruct
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