#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include "circular_queue.h"

/******************************************************************************
 * Definitions
******************************************************************************/
#define QUEUE_SIZE (5U)
#define DATA_ARRAY_SIZE (88U)

/******************************************************************************
 * Prototypes
******************************************************************************/
/*
 * @brief : Display the queue
*/
void display(circularQueue_t *queue);

/******************************************************************************
 * Variables
******************************************************************************/
/* Data */
uint32_t queue_data_array[DATA_ARRAY_SIZE] = {};

/* Queue */
circularQueue_t testQueue =
{
    .front = -1,
    .rear = -1,
    .size = QUEUE_SIZE,
    .queueArray = queue_data_array
};

/******************************************************************************
 * Code
******************************************************************************/
int main(void)
{
    uint32_t data = 88U;

    /* Print empty queue */
    display(&testQueue);

    /* Pop data from empty queue */
    if (circularQueue_PopData(&testQueue, &data))
    {
        printf("data = %d\n", data);
    }
    else
    {
        printf("Can not pop data from queue being empty\n");
    }
    putchar('\n');

    /* Push data into queue */
    circularQueue_PushData(&testQueue, 3U);
    circularQueue_PushData(&testQueue, 1U);
    circularQueue_PushData(&testQueue, 4U);
    circularQueue_PushData(&testQueue, 2U);
    circularQueue_PushData(&testQueue, 5U);
    display(&testQueue);
    putchar('\n');

    /* Push data into full queue */
    if (circularQueue_PushData(&testQueue, 6U))
    {
        display(&testQueue);
    }
    else
    {
        printf("Can not push data to queue being full\n");
    }
    putchar('\n');

    /* Pop data out of queue having data */
    circularQueue_PopData(&testQueue, &data);
    printf("data = %d\n", data);
    display(&testQueue);
    putchar('\n');

    /* Push data into queue having data */
    circularQueue_PushData(&testQueue, 6U);
    display(&testQueue);
    putchar('\n');

    /* Pop all data out of queue */
    circularQueue_PopData(&testQueue, &data);
    circularQueue_PopData(&testQueue, &data);
    circularQueue_PopData(&testQueue, &data);
    circularQueue_PopData(&testQueue, &data);
    circularQueue_PopData(&testQueue, &data);
    display(&testQueue);

    return 0;
}

/*
 * @brief : Display the queue
*/
void display(circularQueue_t *queue)
{
    uint8_t i = 0;

    if (circularQueue_IsEmpty(queue))
    {
        printf("Queue is empty\n");
    }
    else
    {
        printf("queue->front = %d\n", queue->front);
        printf("queue->rear = %d\n", queue->rear);
        printf("queue->queueArray =");
        for (i = queue->front; i != queue->rear; i = ((i + 1U) % queue->size))
        {
            printf("%3d", queue->queueArray[i]);
        }
        printf("%3d\n", queue->queueArray[i]);
    }
}
