//Algorithm for the Parallel Binary Search

#include <stdio.h>
#include <omp.h>
#include <time.h>
#include <stdlib.h>



int main(){

    //variable declaration
    int size;
    int a[size];
    int left, right, token;

    printf("scegli il numeroo di elementi dell'array");

    scanf("%d", &size);


    //random generating array element
    for(int i = 0; i<size; i++){
        a[i] = i;
    }

    printf("scegli il numeroo da cercare");

    scanf("%d", &token);



}


int binarySearch(int a[], int left, int right,int size, int token){
    int mid = size/2;

    #pragma omp parallel for

    if(a[left] > a[right]){
        return -1;
    }

    else if (a[mid] == token){
        return a[mid];
    } 
    else if(a[mid] < token){
        return binarySearch(a, mid+1, right, size, token);
    }
    else 
    {
        return binarySearch(a, left, mid-1, size, token);
    }


}