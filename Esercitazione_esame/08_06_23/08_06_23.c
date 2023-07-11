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

    printf("size riga\n");
    scanf("%d", &row);


    printf("size colonna\n");
    scanf("%d", &cols);



 int ***Bloc = (int ***)calloc(2 , sizeof(int **));

    // Allocazione di ogni matrice nell'array
    for (int i = 0; i < 2; i++) {
        // Allocazione della matrice
        Bloc[i] = (int **)calloc(cols, sizeof(int *));
        for (int j = 0; j < cols; j++) {
            Bloc[i][j] = (int *)calloc((row/2), sizeof(int));
        }
    }


    matrix = calloc(row, sizeof(int *));


    for(int i = 0; i<row; i++)
    {
        matrix[i] = calloc(cols, sizeof(int));
    }

    

            for(int i = 0; i<row; i++)
            {
                for(int j = 0; j < cols; j++)
                {
                    matrix[i][j] = rand()%21;
                }
            }



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

        #pragma omp parallel for
        for(int k = 0; k<2; k++)
        {
            for(int i = 0; i < row; i++)
            {
                for(int j = 0; j<cols; j++)
                {
                    Bloc[k][j][i] = matrix[i][j];
                }
            }
        
        }


        for(int k = 0; k<2; k++)
        {
            for(int i = 0; i < row; i++)
            {
                for(int j = 0; j<cols; j++)
                {
                    printf("%d  ",Bloc[k][j][i]);
                }
            } printf("\n");
        
        }printf("\n");


	
}
