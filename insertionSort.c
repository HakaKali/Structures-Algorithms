/*
Insertion Sort

This repository contains an implementation of the Insertion Sort algorithm in C.
Algorithm Overview

Insertion Sort is a simple sorting algorithm that builds the final sorted array one element at a time. It iterates through the array and for each element, it compares it with the previous elements and shifts them to the right if they are greater, until the correct position for the element is found. This process is repeated for all elements, resulting in a sorted array.

The steps of the Insertion Sort algorithm are as follows:

    Start with the second element and iterate through the array.
    Compare the current element with the elements before it.
    If an element is greater than the current element, shift it one position to the right.
    Repeat step 3 until all elements greater than the current element have been shifted.
    Insert the current element in its correct position.
    Repeat steps 2-5 until all elements have been processed.
*/
#include <stdio.h>

void insertionSort(int arr[], int n) {
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;

        /* Move elements of arr[0..i-1], that are greater than key,
        to one position ahead of their current position */
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void printArray(int arr[], int n) {
    int i;
    for (i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int arr[] = {12, 11, 13, 5, 6};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Array before sorting:\n");
    printArray(arr, n);

    insertionSort(arr, n);

    printf("\nArray after sorting:\n");
    printArray(arr, n);

    return 0;
}
