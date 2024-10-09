/*
 * Queue.c
 *
 *  Created on: Sep 27, 2024
 *      Author: Mohamed Elsayed
 */

#include "Queue.h"

queue_status_t fifoInit(queue_t *q, type_t *buffer, uint32 length){
    if(!q || !buffer){
        return QUEUE_NULL;
    } else {
        q->count = 0;
        q->length = length;
        q->base = buffer;
        q->head = buffer;
        q->tail = buffer;
        return QUEUE_OK;
    }
}

queue_status_t fifoEnqueue(queue_t *q, type_t data){
    if(!q){
        return QUEUE_NULL;
    } else {
        if(queueIsFull(q) == QUEUE_FULL){
            return QUEUE_FULL;
        } else {
            *(q->head) = data;
            q->head++;
            // Wrapping the head if it exceeds the buffer length
            if(q->head >= q->base + q->length){
                q->head = q->base; // Wrap around to the start
            }
            q->count++;
        }
        return QUEUE_OK;
    }
}

queue_status_t fifoDequeue(queue_t *q, type_t *data){
    if(!q || !data){
        return QUEUE_NULL;
    } else {
        if(queueIsEmpty(q) == QUEUE_EMPTY){
            return QUEUE_EMPTY;
        } else {
            *data = *(q->tail);
            q->tail++;
            // Wrapping the tail if it exceeds the buffer length
            if(q->tail >= q->base + q->length){
                q->tail = q->base; // Wrap around to the start
            }
            q->count--;
        }
        return QUEUE_OK;
    }
}

queue_status_t queueDisplay(queue_t *q){
	if(!q){
		return QUEUE_NULL;
	} else {
		if(queueIsEmpty(q) == QUEUE_EMPTY){
			printf("Queue is empty, can't display any data.\n");
			return QUEUE_EMPTY;
		} else {
			type_t *temp = q->tail;
			printf("\n=================Queue(FIFO)===============\n");
			for(int i = 0; i < q->count; i++){
				printf("\t %d \n", *temp);
				temp++;
				if(temp >= q->base + q->length){
	                temp = q->base; // Wrap around to the start
	            }

			}
			printf("============================================\n");
		}
		return QUEUE_OK;
	}
}

queue_status_t queueIsFull(queue_t *q){
    return (q->count == q->length) ? QUEUE_FULL : QUEUE_NOT_FULL;
}

queue_status_t queueIsEmpty(queue_t *q){
    return (q->count == 0) ? QUEUE_EMPTY : QUEUE_NOT_EMPTY;
}

