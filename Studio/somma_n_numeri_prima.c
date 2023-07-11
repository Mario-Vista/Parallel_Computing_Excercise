//prima strategia: ogni thread calcolax
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void fill_array(int *, int);
void print_array(int *, int);


int main()
{
    srand(time(NULL));

    int *a;
    int size;

    printf("Inserire size array\n");
    scanf("%d", &size);

    a = calloc(size, sizeof(int));

    fill_array(a, size);
    puts("a: ");
    print_array(a, size);
    putchar('\n');

    int i, nloc, remainder, step, id, n_thread;

    int sum = 0, localsum = 0;

    #pragma omp parallel shared(a, n_thread, size, sum) private(i, nloc, step, remainder, id, localsum)
    {
        id = omp_get_thread_num();
        n_thread = omp_get_num_threads();

        nloc = size/n_thread;
        remainder = size%n_thread;

        if(id < remainder)
        {
            nloc++;
            step = 0;
        } else {
            step = remainder;
        }

        for(i = 0; i < nloc; i++)
        {
            int index = i+id*nloc+step;
            localsum +=a[index];
        }
        #pragma omp critical
        {
            sum+=localsum;
        }
    }
    printf("Global sum: %d\n", sum);
    free(a);

    return 0;

}


void fill_array(int *array, int size)
{
    for(int i = 0; i < size; i++)
    {
        array[i] = rand()%50;
    }
}

void print_array(int *array, int size)
{
    for(int i = 0; i < size; i++)
    {
        printf("%d ", array[i]);
    }
}