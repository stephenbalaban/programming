#include "qsort.h"
#include <stdio.h>
#define TERMCHAR 2147483647 // largest C int ? [32-bit]
/**
 * print a list
 */
void print_list(int list[]) {
    int i,
        size = count(list);
    printf("[ ");
    for(i = 0; i < size - 1; i++) {
        printf("%d, ", list[i]);
    }
    printf("%d ]\n", list[i]);
}
/**
 * Count a list
 */
int count(int list[]) {
    int i, c;
    for(i = 0; (c = list[i]) != TERMCHAR; i++)
        ;
    return i;
}

/**
 * Inplace swap
 */
void swap(int v[], int i, int j) {
    int tmp = v[i];
    v[i] = v[j];
    v[j] = tmp;
}
/**
 * Quicksort algorithm - C. A. R. Hoare 1962
 * list - a list of integers to be sorted
 * left - the start of the list
 * right - the end of the list
 */
void qsort(int list[], int left, int right) {
    int i, last, partition;
    if (left >= right)
        return;
    partition = (left + right) / 2;
    swap(list, left, partition);;
    last = left;
    for ( i = left + 1; i <= right; i++)
        if (list[i] < list[left])
            swap(list, ++last, i);
    swap(list, left, last);
    qsort(list, left, last-1);
    qsort(list, last+1, right);
}

/**
 * Generic sorting wrapper
 */
void sort_list(int list[]) {
    printf("Sorting the list...\n");
    qsort(list, 0, count(list));
}

int main(int argc, char* argv[]) {
    int list[] = { 30, 1, 3, 6, 7, 8, 4, 16, 29, 10, 11, 12, 20, 5, 9, 23, 26,
                   22, 24, 13, 14, 17, 18, 19, 27, 28, 2, 25, TERMCHAR };
    int list_length = count(list);
    printf("Got a list of length: %d\n", list_length);
    print_list(list);
    sort_list(list);
    print_list(list);
}
