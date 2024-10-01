/*
 * main.c
 *
 *  Created on: Sep 27, 2024
 *      Author: Mohamed Elsayed
 */

#include "Queue.h"
#include <stdio.h>

#define QUEUE_SIZE 5

int main() {
    queue_t myQueue;
    type_t buffer[QUEUE_SIZE];
    queue_status_t status;
    type_t data;

    // Initialize the queue
    status = fifoInit(&myQueue, buffer, QUEUE_SIZE);
    if (status == QUEUE_OK) {
        printf("Queue initialized successfully.\n");
    } else {
        printf("Queue initialization failed.\n");
        return -1;
    }

    // Test Enqueue operation
    printf("Enqueueing elements...\n");
    for (type_t i = 0; i < 6; i++) {
        status = fifoEnqueue(&myQueue, i * 10);  // Enqueue 0, 10, 20, 30, 40
        if (status == QUEUE_OK) {
            printf("Enqueued: %d\n", i * 10);
        } else if (status == QUEUE_FULL) {
            printf("Failed to enqueue %d: Queue is full.\n", i * 10);
        }
    }

    // Test if the queue is full
    if (queueIsFull(&myQueue) == QUEUE_FULL) {
        printf("Queue is full.\n");
    } else {
        printf("Queue is not full.\n");
    }

    // Display the queue
    queueDisplay(&myQueue);

    // Test Dequeue operation
    printf("\nDequeueing elements...\n");
    for (type_t i = 0; i < 6; i++) {
        status = fifoDequeue(&myQueue, &data);  // Dequeue elements
        if (status == QUEUE_OK) {
            printf("Dequeued: %d\n", data);
        } else if (status == QUEUE_EMPTY) {
            printf("Failed to dequeue: Queue is empty.\n");
        }
    }

    // Test if the queue is empty
    if (queueIsEmpty(&myQueue) == QUEUE_EMPTY) {
        printf("Queue is empty.\n");
    } else {
        printf("Queue is not empty.\n");
    }

    return 0;
}
