/*
Bucket Sort

This repository contains an implementation of the Bucket Sort algorithm in C.
Algorithm Overview

Bucket Sort is a sorting algorithm that divides the input into different buckets or bins, each representing a range of values. The elements are then distributed into these buckets based on their values. Each bucket is individually sorted, either using another sorting algorithm or recursively applying the bucket sort algorithm. Finally, the sorted elements from each bucket are concatenated to obtain the final sorted array.

The steps of the Bucket Sort algorithm are as follows:

    Create an array of empty buckets.
    Iterate through the input array and distribute the elements into the corresponding buckets based on their values.
    Sort each bucket individually, either using another sorting algorithm or recursively applying the bucket sort algorithm if the range of values is large.
    Concatenate the sorted elements from each bucket to obtain the final sorted array.
*/
#include <stdio.h>
#include <stdlib.h>

// Structure for a bucket (linked list node)
struct BucketNode {
    int data;
    struct BucketNode* next;
};

// Function to insert an element into a bucket (linked list)
void insert(struct BucketNode** bucket, int value) {
    struct BucketNode* newNode = (struct BucketNode*)malloc(sizeof(struct BucketNode));
    newNode->data = value;
    newNode->next = NULL;

    if (*bucket == NULL) {
        *bucket = newNode;
    } else {
        struct BucketNode* temp = *bucket;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

// Function to sort each bucket using insertion sort
void sortBucket(struct BucketNode* bucket) {
    if (bucket == NULL || bucket->next == NULL) {
        return;
    }

    struct BucketNode *i, *j;
    int key;

    for (i = bucket->next; i != NULL; i = i->next) {
        key = i->data;
        j = i->next;

        while (j != NULL && j->data < key) {
            i->data = j->data;
            i = i->next;
            j = j->next;
        }

        i->data = key;
    }
}

// Function to concatenate all the buckets into a single sorted array
void concatenateBuckets(struct BucketNode** buckets, int arr[], int numBuckets) {
    int index = 0;
    for (int i = 0; i < numBuckets; i++) {
        struct BucketNode* temp = buckets[i];
        while (temp != NULL) {
            arr[index++] = temp->data;
            temp = temp->next;
        }
    }
}

// Function to perform bucket sort
void bucketSort(int arr[], int n, int numBuckets) {
    // Create an array of empty buckets
    struct BucketNode** buckets = (struct BucketNode**)malloc(numBuckets * sizeof(struct BucketNode*));
    for (int i = 0; i < numBuckets; i++) {
        buckets[i] = NULL;
    }

    // Insert elements into buckets
    for (int i = 0; i < n; i++) {
        int bucketIndex = arr[i] * numBuckets / (100 + 1);
        insert(&buckets[bucketIndex], arr[i]);
    }

    // Sort each bucket using insertion sort
    for (int i = 0; i < numBuckets; i++) {
        sortBucket(buckets[i]);
    }

    // Concatenate all the buckets into a single sorted array
    concatenateBuckets(buckets, arr, numBuckets);

    // Free memory allocated for buckets
    for (int i = 0; i < numBuckets; i++) {
        struct BucketNode* temp = buckets[i];
        while (temp != NULL) {
            struct BucketNode* prev = temp;
            temp = temp->next;
            free(prev);
        }
    }
    free(buckets);
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
    int arr[] = {29, 25, 3, 49, 9, 37, 21};
    int n = sizeof(arr) / sizeof(arr[0]);
    int numBuckets = 5;

    printf("Array before sorting:\n");
    printArray(arr, n);

    bucketSort(arr, n, numBuckets);

    printf("Array after sorting:\n");
    printArray(arr, n);

    return 0;
}
