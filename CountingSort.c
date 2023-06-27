/*
Counting Sort

This repository contains an implementation of the Counting Sort algorithm in C.
Algorithm Overview

Counting Sort is a linear sorting algorithm that works by determining, for each input element, the number of elements that are less than it. Based on this information, the elements are then placed in their correct sorted positions. Counting Sort assumes that the input consists of integers within a specific range.

The steps of the Counting Sort algorithm are as follows:

    Find the maximum element in the input array to determine the range of counting.
    Create a count array of size max + 1, initialized with zeros.
    Traverse the input array and count the occurrences of each element, storing the count in the count array.
    Modify the count array to contain the actual positions of the elements in the sorted output.
    Build the sorted output array by iterating through the input array and placing each element in its correct position based on the count array.
    The output array now contains the sorted elements.
*/
#include <stdio.h>

// Function to perform counting sort
void countingSort(int arr[], int n, int max) {
    int count[max + 1]; // Create a count array to store the count of each element
    int output[n]; // Create an output array to store the sorted elements

    // Initialize count array with zeros
    for (int i = 0; i <= max; i++) {
        count[i] = 0;
    }

    // Store the count of each element in count array
    for (int i = 0; i < n; i++) {
        count[arr[i]]++;
    }

    // Modify the count array to store the actual position of each element
    for (int i = 1; i <= max; i++) {
        count[i] += count[i - 1];
    }

    // Build the output array
    for (int i = n - 1; i >= 0; i--) {
        output[count[arr[i]] - 1] = arr[i];
        count[arr[i]]--;
    }

    // Copy the sorted elements back to the original array
    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }
}

// Function to print an array
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// Driver code
int main() {
    int arr[] = {4, 2, 2, 8, 3, 3, 1};
    int n = sizeof(arr) / sizeof(arr[0]);
    int max = 8; // Maximum element in the array

    printf("Array before sorting:\n");
    printArray(arr, n);

    countingSort(arr, n, max);

    printf("Array after sorting:\n");
    printArray(arr, n);

    return 0;
}
