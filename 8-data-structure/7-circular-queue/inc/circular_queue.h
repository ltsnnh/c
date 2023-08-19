#ifndef __CIRCULAR_QUEUE_H__
#define __CIRCULAR_QUEUE_H__

/******************************************************************************
 * Definitions
******************************************************************************/
/* Define queue type (FIFO) */
typedef struct
{
    int8_t front;   /* POP */
    int8_t rear;    /* PUSH */
    int8_t size;    /* size of ring buffer */
    uint32_t * queueArray;  /* point to data array */
} circularQueue_t;

/******************************************************************************
 * API
******************************************************************************/
/*
 * @brief : Check full of queue
*/
bool circularQueue_IsFull(const circularQueue_t* const queue);

/*
 * @brief : Check empty of queue
*/
bool circularQueue_IsEmpty(const circularQueue_t* const queue);

/*
 * @brief : Handing push data into queue
 *
 * @note : This function frequently return void due to being called in
 *  interrupt handler
*/
bool circularQueue_PushData(circularQueue_t* const queue,
                            const uint32_t inputData);

/*
 * @brief : Handing pop data out of queue
*/
bool circularQueue_PopData(circularQueue_t* const queue,
                           uint32_t* const outputData);

#endif  /* __CIRCULAR_QUEUE_H__ */
