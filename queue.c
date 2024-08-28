#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

// Initialize a queue
void init_queue(Queue* queue) {
    queue->head = NULL;
    queue->tail = NULL;
}

// Check if the queue is empty
int is_empty(Queue* queue) {
    return queue->head == NULL;
}

// Enqueue an element into the queue
void enqueue(Queue* queue, int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (!new_node) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    new_node->data = data;
    new_node->next = NULL;
    new_node->prev = queue->tail;
    if (queue->tail) {
        queue->tail->next = new_node;
    }
    queue->tail = new_node;
    if (!queue->head) {
        queue->head = new_node;
    }
}

// Dequeue (service) an element from the queue
int service(Queue* queue) {
    if (is_empty(queue)) {
        fprintf(stderr, "Queue is empty\n");
        return -1;  // Return -1 if the queue is empty
    }
    int data = queue->head->data;
    Node* temp = queue->head;
    queue->head = queue->head->next;
    if (queue->head) {
        queue->head->prev = NULL;
    } else {
        queue->tail = NULL;
    }
    free(temp);
    return data;
}

// Free all nodes in the queue
void free_queue(Queue* queue) {
    while (!is_empty(queue)) {
        service(queue);
    }
}
