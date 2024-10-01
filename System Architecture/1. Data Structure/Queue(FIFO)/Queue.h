/*
 * Queue.h
 *
 *  Created on: Sep 27, 2024
 *      Author: Mohamed Elsayed
 */

#ifndef QUEUE_H_
#define QUEUE_H_

#include <stdio.h>
#include "Platform_Types.h"

#define QUEUE_MAX_SIZE 5
#define type_t uint8

typedef struct{
	uint32 length;
	uint32 count;
	type_t *base;
	type_t *head;
	type_t *tail;
}queue_t;

typedef enum{
	QUEUE_OK,
	QUEUE_NULL,
	QUEUE_EMPTY,
	QUEUE_NOT_EMPTY,
	QUEUE_FULL,
	QUEUE_NOT_FULL
}queue_status_t;


queue_status_t fifoInit(queue_t *q, type_t *buffer, uint32 length);
queue_status_t fifoEnqueue(queue_t *q, type_t data);
queue_status_t fifoDequeue(queue_t *q, type_t *data);
queue_status_t queueDisplay(queue_t *q);
queue_status_t queueIsFull(queue_t *q);
queue_status_t queueIsEmpty(queue_t *q);

#endif /* QUEUE_H_ */
