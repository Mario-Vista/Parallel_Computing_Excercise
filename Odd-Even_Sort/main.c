//Example main for Odd Even sort parallel algorithm

#include <stdlib.h>
#include <time.h>
#include "oddEvenSort.h"

int main(){

    int N = 10, a[N];
    srand(time(NULL));

    for(int i = 0; i < N; i++){
        a[i] = rand() % 11;
    }

    oddEvenSort(a, N);

    for(int i = 0; i < N; i++){
        printf("%d\n", a[i]);
    }

    return 0;
}