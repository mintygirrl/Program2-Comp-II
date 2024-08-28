#ifndef QUEUE_H
#define QUEUE_H

// Define the Node structure
typedef struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
} Node;

// Define the Queue structure
typedef struct Queue {
    Node* head;
    Node* tail;
} Queue;

// Function to initialize a queue
void init_queue(Queue* queue);

// Function to check if the queue is empty
int is_empty(Queue* queue);

// Function to enqueue an element into the queue
void enqueue(Queue* queue, int data);

// Function to dequeue (service) an element from the queue
int service(Queue* queue);

// Function to free all nodes in the queue
void free_queue(Queue* queue);

#endif // QUEUE_H
