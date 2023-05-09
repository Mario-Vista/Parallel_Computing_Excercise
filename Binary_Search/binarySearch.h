// Binary Search algorithm using OMP parallel

#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

int binary(int l, int r, int key, int n, int *a){
    int index = -1;
    int size = (r-l+1)/n;

    // If the range is small enough or there is only one thread,
    // perform a sequential search within the range
    if(size == 0 || n == 1){
        #pragma omp parallel for
        for(int i = l; i <= r; i++){
            if(a[i] == key){
                index = i;
            }
        }
        return index;
    }

    int left = l;
    int right = r;

    //If the size of the subrange allows for parallelization, the code sets the number of 
    //threads and enables nested parallelism using omp_set_num_threads and omp_set_nested.
    omp_set_num_threads(n);
    omp_set_nested(1);
    
    #pragma omp parallel
    {
        int id = omp_get_thread_num();
        int lt = l + id * size;
        int rt = lt + size - 1;

        // Adjust the last thread's range to cover the remaining elements
        if(id == n-1){
            rt = r;
        }

        // Check if the key lies within the thread's subrange
        if(a[lt] <= key && a[rt] >= key){
            left = lt;
            right = rt;
        }
    }

    // If the subrange has not changed, the key is not found
    if(left == l && right == r){
        return -1;
    }

    // Recursively search within the updated subrange
    return binary(left, right, key, n, a);
}
