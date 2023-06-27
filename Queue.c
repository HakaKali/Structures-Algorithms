#include <stdio.h>
#include <stdlib.h>

// Structure for a queue node
struct QueueNode {
    int data;
    struct QueueNode* next;
};

// Structure for a queue
struct Queue {
    struct QueueNode *front, *rear;
};

// Function to create a new queue
struct Queue* createQueue() {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->front = queue->rear = NULL;
    return queue;
}

// Function to check if the queue is empty
int isEmpty(struct Queue* queue) {
    return (queue->front == NULL);
}

// Function to enqueue an element to the queue
void enqueue(struct Queue* queue, int value) {
    struct QueueNode* newNode = (struct QueueNode*)malloc(sizeof(struct QueueNode));
    newNode->data = value;
    newNode->next = NULL;

    if (isEmpty(queue)) {
        queue->front = queue->rear = newNode;
    } else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
}

// Function to dequeue an element from the queue
int dequeue(struct Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty.\n");
        return -1;
    }

    struct QueueNode* temp = queue->front;
    int value = temp->data;
    queue->front = queue->front->next;

    if (queue->front == NULL) {
        queue->rear = NULL;
    }

    free(temp);
    return value;
}

// Function to print the elements of the queue
void printQueue(struct Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty.\n");
        return;
    }

    struct QueueNode* temp = queue->front;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

// Driver code
int main() {
    struct Queue* queue = createQueue();

    enqueue(queue, 10);
    enqueue(queue, 20);
    enqueue(queue, 30);
    enqueue(queue, 40);

    printf("Queue elements: ");
    printQueue(queue);

    int value = dequeue(queue);
    printf("Dequeued element: %d\n", value);

    printf("Queue elements after dequeue: ");
    printQueue(queue);

    return 0;
}
