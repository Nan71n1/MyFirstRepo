// Program to measure the time required for heapsort

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(int *arr, int i, int size) {
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    int max = i;

    if(l < size && arr[l] > arr[max]) {
        max = l;
    }
    if(r < size && arr[r] > arr[max]){
        max = r;
    } 
    if(max != i) {
        swap(&arr[i], &arr[max]);
        heapify(arr, max, size);
    }
}


// return time required to sort
double heapSort(int *arr, int size) {
    clock_t t;
    t = clock();

    for(int i = size/2 - 1; i >= 0; i--) {
        heapify(arr, i, size);
    }

    for(int i = size-1; i>=0; i--) {
        swap(&arr[0], &arr[i]);
        heapify(arr, 0, i);
    }

    t = clock() - t;
    return ((double)t) / CLOCKS_PER_SEC;
}

void printArray(int *arr, int size) {
    for(int i = 0; i < size; i++) 
        printf("%d ", *(arr+i));
    printf("\n");
}

void fillArray(int *arr, int size) {
    for(int i = 0; i < size; i++) {
        arr[i] = rand() % INT_MAX;
    }
}

int main()
{
    system("clear");
    int size = 1;
    double time;
    printf("Size\t\tTime\n");

    for(int i = 1; i <= 8; i++) {
        size *= 10;
        int *arr = malloc(size * sizeof(int));
        fillArray(arr, size);
        time = heapSort(arr, size);
        if(i <=6)
            printf("%d\t\t%lf\n", size, time);
        else 
            printf("%d\t%lf\n", size, time);
        
        free(arr);
    }

    return 0;
}
