//Binary Search using OMP parallel

#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

int binary(int l, int r, int key, int n, int *a){
    int index = -1;
    int size = (r-l+1)/n;
    if(size == 0 || n ==1){
        #pragma omp parallel for
        for(int i = l; i<=r; i++){
            if(a[i] == key){
                index = i;
            }
        }
            return index;
    }

    int left = l;
    int right = r;
    omp_set_num_threads(n);
    omp_set_nested(1);
    
    #pragma omp parallel
    {
        int id = omp_get_thread_num();
        int lt = l+id*size;
        int rt = lt+size-1;

        if(id == n-1){
            rt = r;
        }

        if(a[lt] <= key && a[rt] >= key){
            left = lt;
            right = rt;
        }

    }
    if(left == l && right == r){
        return -1;
    }


    return binary(left, right, key, n, a);
}
