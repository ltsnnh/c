#include <stdint.h>
#include <stdbool.h>
#include "circular_queue.h"

/******************************************************************************
 * Code
******************************************************************************/
/*
 * @brief : Check full of queue
*/
bool circularQueue_IsFull(const circularQueue_t* const queue)
{
    bool retVal = false;

    if ((queue->front == (queue->rear + 1U)) || \
       ((queue->front == 0) && (queue->rear == queue->size - 1U)))
    {
        retVal = true;
    }

    return retVal;
}

/*
 * @brief : Check empty of queue
*/
bool circularQueue_IsEmpty(const circularQueue_t* const queue)
{
    bool retVal = false;

    if (queue->front == -1)
    {
        retVal = true;
    }

    return retVal;
}

/*
 * @brief : Handing push data into queue
*/
bool circularQueue_PushData(circularQueue_t* const queue,
                            const uint32_t inputData)
{
    bool retVal = true;

    if (!circularQueue_IsFull(queue))
    {
        if (queue->front == -1)
        {
            queue->front = 0;
        }
        queue->rear = (queue->rear + 1) % queue->size;
        queue->queueArray[queue->rear] = inputData;
    }
    else
    {
        retVal = false;
    }

    return retVal;
}

/*
 * @brief : Handing pop data out of queue
*/
bool circularQueue_PopData(circularQueue_t* const queue,
                           uint32_t* const outputData)
{
    bool retVal = true;

    if (!circularQueue_IsEmpty(queue))
    {
        *outputData = queue->queueArray[queue->front];
        if (queue->front == queue->rear)
        {
            queue->front = -1;
            queue->rear = -1;
        }
        else
        {
            queue->front = (queue->front + 1U) % queue->size;
        }
    }
    else
    {
        retVal = false;
    }

    return retVal;
}
