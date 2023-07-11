/*
Implementare un programma parallelo per lpambiente multicore con npxnp
unità processanti che impieghi la libreria OpenMP. Il programma deve essere organizzato come segue:
    Il core master deve leggere una matrice A di dimensione NxM
    
    I core devono organizzarsi per estrarre ognuno una sottomatrice, decomponendo la matrice A
    per blocchi riga, e costruendo la trasposta di tale sottomatrice in una matrice B_loc

    Infine i core devono collaborare per sommare le sotto matrici estratte
    B_loc in un'unica matrice finale C

    Il core master stampa la matrice risultato e il tempo d'esecuzione
*/

#include <omp.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    srand(time(NULL));
    int **matrix;
    int row, cols;
    int **B_loc;

    printf("size riga\n");
    scanf("%d", &row);


    printf("size colonna\n");
    scanf("%d", &cols);


    matrix = calloc(row, sizeof(int *));
    B_loc = calloc(cols, sizeof(int *));

    for(int i = 0; i<row; i++)
    {
        matrix[i] = calloc(cols, sizeof(int));
    }

    for(int i = 0; i<cols; i++)
    {
        B_loc[i] = calloc(row, sizeof(int));
    }
    

            for(int i = 0; i<row; i++)
            {
                for(int j = 0; j < cols; j++)
                {
                    matrix[i][j] = rand()%21;
                }
            }


    #pragma omp parallel for
    {	
        #pragma omp master
        {
            for(int i = 0; i<row; i++)
            {
                for(int j = 0; j < cols; j++)
                {
                printf("%d   ", matrix[i][j]);
                }
                printf("\n");
            }
        }  

        for(int i = 0; i < row; i++)
        {
            for(int j = 0; j<cols; j++)
            {
                B_loc[j][i] = matrix[i][j];
            }
        }
    }


	
}

