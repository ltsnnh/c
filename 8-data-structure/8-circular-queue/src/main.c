#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "circular_queue.h"

#define NUM_ELEMENTS (3U)

uint8_t dataArray[NUM_ELEMENTS][QUEUE_ELEMENT_LENGTH] = {0};

circularQueue_t testQueue =
{
    .front = -1,
    .rear = -1,
    .size = NUM_ELEMENTS,
    .queueArray = dataArray
};

int main(void)
{
    uint8_t *pTr = NULL;
    uint8_t i = 0;
    uint8_t j = 0;

    /* Empty queue */
    if (circularQueue_IsFull(&testQueue))
    {
        printf("Queue is full\n");
    }
    if (circularQueue_IsEmpty(&testQueue))
    {
        printf("Queue is Empty\n");
    }

    /* Push to queue (1) */
    if (circularQueue_PushData(&testQueue, &pTr))
    {
        printf("%d\n", testQueue.front);
        printf("%d\n", testQueue.rear);
    }

    /* Push to queue (2) */
    if (circularQueue_PushData(&testQueue, &pTr))
    {
        printf("%d\n", testQueue.front);
        printf("%d\n", testQueue.rear);
    }

    /* Push to queue (3) */
    if (circularQueue_PushData(&testQueue, &pTr))
    {
        printf("%d\n", testQueue.front);
        printf("%d\n", testQueue.rear);
    }

    /* Full queue */
    if (circularQueue_IsFull(&testQueue))
    {
        printf("Queue is full\n");
    }
    if (circularQueue_IsEmpty(&testQueue))
    {
        printf("Queue is Empty\n");
    }

    /* Pop from queue (3) */
    if (circularQueue_PopData(&testQueue, &pTr))
    {
        printf("%d\n", testQueue.front);
        printf("%d\n", testQueue.rear);
    }

    /* Pop from queue (2) */
    if (circularQueue_PopData(&testQueue, &pTr))
    {
        printf("%d\n", testQueue.front);
        printf("%d\n", testQueue.rear);
    }

    /* Fill data to dataArray[1][...] */
    for (i = 0; i < QUEUE_ELEMENT_LENGTH; i++)
    {
        pTr[i] = i;
    }

    /* Pop from queue (1) */
    if (circularQueue_PopData(&testQueue, &pTr))
    {
        printf("%d\n", testQueue.front);
        printf("%d\n", testQueue.rear);
    }

    /* Empty queue */
    if (circularQueue_IsFull(&testQueue))
    {
        printf("Queue is full\n");
    }
    if (circularQueue_IsEmpty(&testQueue))
    {
        printf("Queue is Empty\n");
    }

    /* Print dataArray */

    for (i = 0; i < NUM_ELEMENTS; i++)
    {
        for (j = 0; j < QUEUE_ELEMENT_LENGTH; j++)
        {
            printf("%d\t", dataArray[i][j]);
        }
        putchar('\n');
    }

    return 0;
}
