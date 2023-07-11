#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

void fill_array(double *, int);
void print_array(double *, int);

int main()
{
    srand(time(NULL));
    int size, nloc, remainder, step, id, n_thread, i;
    printf("Inserire size array\n");
    scanf("%d", &size);
    double *a, *b, *c;
    a = calloc(size, sizeof(double));
    b = calloc(size, sizeof(double));
    c = calloc(size, sizeof(double));

    fill_array(a, size);
    fill_array(b, size);

    #pragma omp parallel shared(a, b, c, n_thread, size) private(i, nloc, remainder, step,  id)
    {
        id = omp_get_thread_num();
        n_thread = omp_get_num_threads();

        nloc = size/n_thread;

        remainder = size%n_thread;

        if(id < remainder)
        {
            nloc++;
            step = 0;
        } else
        {
            step = remainder;
        }

        for(i = 0; i < nloc; i++)
        {
            int index = i+id * nloc + step;
            c[index] = a[index] + b[index];
        }
    }

    printf("Array a: \n");
    print_array(a, size);

    printf("\nArray b: \n");
    print_array(b, size);
    
    printf("\nArray c: \n");
    print_array(c, size);

    free(a);
    free(b);
    free(c);

    return 0;
}

void fill_array(double *array, int size)
{
    for(int i = 0; i < size; i++)
    {
        array[i] = rand()%50;
    }
}

void print_array(double *array, int size)
{
    for(int i = 0; i < size; i++)
    {
        printf("%f ", array[i]);
    }
}