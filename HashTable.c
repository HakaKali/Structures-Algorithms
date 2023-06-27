#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 10

// Structure for a hash table node
struct HashNode {
    int key;
    int value;
    struct HashNode* next;
};

// Structure for a hash table
struct HashTable {
    struct HashNode* table[TABLE_SIZE];
};

// Function to create a new hash table
struct HashTable* createHashTable() {
    struct HashTable* hashTable = (struct HashTable*)malloc(sizeof(struct HashTable));
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable->table[i] = NULL;
    }
    return hashTable;
}

// Function to calculate the hash value for a key
int hashFunction(int key) {
    return key % TABLE_SIZE;
}

// Function to insert a key-value pair into the hash table
void insert(struct HashTable* hashTable, int key, int value) {
    int index = hashFunction(key);
    struct HashNode* newNode = (struct HashNode*)malloc(sizeof(struct HashNode));
    newNode->key = key;
    newNode->value = value;
    newNode->next = NULL;

    if (hashTable->table[index] == NULL) {
        hashTable->table[index] = newNode;
    } else {
        struct HashNode* temp = hashTable->table[index];
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

// Function to search for a value based on a key in the hash table
int search(struct HashTable* hashTable, int key) {
    int index = hashFunction(key);
    struct HashNode* temp = hashTable->table[index];

    while (temp != NULL) {
        if (temp->key == key) {
            return temp->value;
        }
        temp = temp->next;
    }

    return -1; // Key not found
}

// Function to delete a key-value pair from the hash table
void delete(struct HashTable* hashTable, int key) {
    int index = hashFunction(key);
    struct HashNode* current = hashTable->table[index];
    struct HashNode* previous = NULL;

    while (current != NULL) {
        if (current->key == key) {
            if (previous == NULL) {
                hashTable->table[index] = current->next;
            } else {
                previous->next = current->next;
            }
            free(current);
            return;
        }
        previous = current;
        current = current->next;
    }
}

// Function to print the hash table
void printHashTable(struct HashTable* hashTable) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        struct HashNode* temp = hashTable->table[i];
        printf("Bucket %d: ", i);
        while (temp != NULL) {
            printf("(%d, %d) ", temp->key, temp->value);
            temp = temp->next;
        }
        printf("\n");
    }
}

// Driver code
int main() {
    struct HashTable* hashTable = createHashTable();

    insert(hashTable, 10, 50);
    insert(hashTable, 25, 80);
    insert(hashTable, 42, 35);
    insert(hashTable, 17, 60);

    printf("Hash table after insertions:\n");
    printHashTable(hashTable);

    int searchKey = 25;
    int searchResult = search(hashTable, searchKey);
    if (searchResult != -1) {
        printf("Value for key %d: %d\n", searchKey, searchResult);
    } else {
        printf("Key %d not found.\n", searchKey);
    }

    int deleteKey = 42;
    delete(hashTable, deleteKey);
    printf("Hash table after deletion of key %d:\n", deleteKey);
    printHashTable(hashTable);

    return 0;
}
