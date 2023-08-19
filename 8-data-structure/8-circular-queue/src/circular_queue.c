#include <stdint.h>
#include <stdbool.h>
#include "circular_queue.h"

/******************************************************************************
 * Code
******************************************************************************/
/*
 * @brief Check full of queue
 *
 * @param pQueue A pointer points to queue manager structure
 * @return
 *      - true  - Queue is full
 *      - false - Queue is not full
 */
bool circularQueue_IsFull(const circularQueue_t* const pQueue)
{
    bool retVal = false;

    if ((pQueue->front == (pQueue->rear + 1U)) || \
       ((pQueue->front == 0) && (pQueue->rear == pQueue->size - 1U)))
    {
        retVal = true;
    }

    return retVal;
}

/*
 * @brief Check empty of queue
 *
 * @param pQueue A pointer points to queue manager structure
 * @return
 *      - true  - Queue is empty
 *      - false - Queue is not empty
 */
bool circularQueue_IsEmpty(const circularQueue_t* const pQueue)
{
    bool retVal = false;

    if (pQueue->front == -1)
    {
        retVal = true;
    }

    return retVal;
}

/*
 * @brief Handing push data into queue
 *
 * @param pQueue A pointer points to queue manager structure
 * @param pInput A pointer points a element of queue
 * @return
 *      - true  - Can put data to queue
 *      - false - Queue is full, can not push data to queue
 */
bool circularQueue_PushData(circularQueue_t* const pQueue,
                            uint8_t **pInput)
{
    bool retVal = true;

    if (!circularQueue_IsFull(pQueue))
    {
        if (pQueue->front == -1)
        {
            pQueue->front = 0;
        }
        pQueue->rear = (pQueue->rear + 1) % pQueue->size;
        *pInput = pQueue->queueArray[pQueue->rear];
    }
    else
    {
        retVal = false;
    }

    return retVal;
}

/*
 * @brief Handing pop data out of queue
 *
 * @param pQueue A pointer points to queue manager structure
 * @param pOutput A pointer points a element of queue
 * @return
 *      - true  - Can pop data from queue
 *      - false - Queue is empty, can not pop data from queue
 */
bool circularQueue_PopData(circularQueue_t* const pQueue,
                           uint8_t **pOutput)
{
    bool retVal = true;

    if (!circularQueue_IsEmpty(pQueue))
    {
        *pOutput = pQueue->queueArray[pQueue->front];
        if (pQueue->front == pQueue->rear)
        {
            pQueue->front = -1;
            pQueue->rear = -1;
        }
        else
        {
            pQueue->front = (pQueue->front + 1U) % pQueue->size;
        }
    }
    else
    {
        retVal = false;
    }

    return retVal;
}

/******************************************************************************
 * EOF
******************************************************************************/
