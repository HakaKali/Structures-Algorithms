/*
Radix Sort

This repository contains an implementation of the Radix Sort algorithm in C.
Algorithm Overview

Radix Sort is a linear sorting algorithm that sorts elements based on their digits. It works by sorting the elements based on the least significant digit to the most significant digit. Radix Sort can be applied to integers or strings by considering each character as a digit.

The steps of the Radix Sort algorithm are as follows:

    Find the maximum element in the input array to determine the number of digits.
    Perform counting sort for each digit, starting from the least significant digit to the most significant digit.
    For each digit position, create a count array to store the count of each digit.
    Traverse the input array and count the occurrences of each digit, storing the count in the count array.
    Modify the count array to contain the actual positions of the digits in the sorted output.
    Build the sorted output array by iterating through the input array and placing each element in its correct position based on the digit being considered.
    The output array now contains the sorted elements.
*/
#include <stdio.h>

// Function to find the maximum element in an array
int findMax(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

// Function to perform counting sort based on digit
void countingSort(int arr[], int n, int exp) {
    int output[n]; // Create an output array to store the sorted elements
    int count[10] = {0}; // Create a count array to store the count of each digit

    // Store the count of each digit in count array
    for (int i = 0; i < n; i++) {
        count[(arr[i] / exp) % 10]++;
    }

    // Modify the count array to store the actual position of each digit
    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    // Build the output array
    for (int i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    // Copy the sorted elements back to the original array
    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }
}

// Function to perform radix sort
void radixSort(int arr[], int n) {
    int max = findMax(arr, n); // Find the maximum element in the array

    // Perform counting sort for every digit, starting from the least significant digit
    for (int exp = 1; max / exp > 0; exp *= 10) {
        countingSort(arr, n, exp);
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
    int arr[] = {170, 45, 75, 90, 802, 24, 2, 66};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Array before sorting:\n");
    printArray(arr, n);

    radixSort(arr, n);

    printf("Array after sorting:\n");
    printArray(arr, n);

    return 0;
}
