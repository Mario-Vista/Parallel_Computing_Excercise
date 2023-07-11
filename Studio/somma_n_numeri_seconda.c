//seconda strategia: i processori vengono accoppiati e ognuna manda la propria somma all'altro che la aggrega

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

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

    int i, remainder, step, nloc, n_thread, id, sum;

    #pragma omp parallel shared(a, n_thread, size) private(i, nloc, remainder, step, id)
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
            sum+=a[index];
        }
    }

    printf("Somma: %d", sum);

    free(a);

    return(0);


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