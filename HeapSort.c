/*
Heap Sort

This repository contains an implementation of the Heap Sort algorithm in C.
Algorithm Overview

Heap Sort is a comparison-based sorting algorithm that uses a binary heap data structure. It builds a max heap (for sorting in ascending order) or a min heap (for sorting in descending order) from the input array and then repeatedly extracts the maximum (or minimum) element from the heap, placing it at the end of the array. This process continues until the array is fully sorted.

The steps of the Heap Sort algorithm are as follows:

    Build a max heap from the input array.
    The maximum element (root of the heap) is now at the first position. Swap it with the last element of the heap.
    Remove the last element from the heap (considering it as sorted) and decrease the heap size.
    Heapify the root of the heap to maintain the heap property.
    Repeat steps 2-4 until the heap size becomes 1.
    The array is now sorted.
*/
#include <stdio.h>

// Function to swap two elements
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Function to heapify a subtree rooted at index 'root'
void heapify(int arr[], int n, int root) {
    int largest = root;     // Initialize largest as root
    int left = 2 * root + 1;    // Left child
    int right = 2 * root + 2;   // Right child

    // If left child is larger than root
    if (left < n && arr[left] > arr[largest])
        largest = left;

    // If right child is larger than largest so far
    if (right < n && arr[right] > arr[largest])
        largest = right;

    // If largest is not root
    if (largest != root) {
        swap(&arr[root], &arr[largest]);

        // Recursively heapify the affected sub-tree
        heapify(arr, n, largest);
    }
}

// Main function to perform heap sort
void heapSort(int arr[], int n) {
    // Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // Extract elements from the heap one by one
    for (int i = n - 1; i > 0; i--) {
        // Move the current root to the end
        swap(&arr[0], &arr[i]);

        // Call heapify on the reduced heap
        heapify(arr, i, 0);
    }
}

// Function to print an array
void printArray(int arr[], int n) {
    for (int i = 0; i < n; ++i)
        printf("%d ", arr[i]);
    printf("\n");
}

// Driver code
int main() {
    int arr[] = {12, 11, 13, 5, 6, 7};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Array before sorting:\n");
    printArray(arr, n);

    heapSort(arr, n);

    printf("Array after sorting:\n");
    printArray(arr, n);

    return 0;
}
