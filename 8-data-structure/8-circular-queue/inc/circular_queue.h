#ifndef __CIRCULAR_QUEUE_H__
#define __CIRCULAR_QUEUE_H__

/******************************************************************************
 * Definitions
******************************************************************************/
/* Define length of queue element */
#define QUEUE_ELEMENT_LENGTH (5U)

/* Define queue type (FIFO) */
typedef struct
{
    int8_t front;   /* POP */
    int8_t rear;    /* PUSH */
    uint8_t size;   /* Size of ring buffer */
    uint8_t (*queueArray)[QUEUE_ELEMENT_LENGTH];  /* Point to data array */
} circularQueue_t;

/******************************************************************************
 * API
******************************************************************************/
/*
 * @brief Check full of queue
 *
 * @param queue A pointer points to queue manager structure
 * @return
 *      - true  - Queue is full
 *      - false - Queue is not full
 */
bool circularQueue_IsFull(const circularQueue_t* const pQueue);

/*
 * @brief : Check empty of queue
 *
 * @param queue A pointer points to queue manager structure
 * @return
 *      - true  - Queue is empty
 *      - false - Queue is not empty
 */
bool circularQueue_IsEmpty(const circularQueue_t* const pQueue);

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
                            uint8_t **pInput);

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
                           uint8_t **pOutput);

#endif  /* __CIRCULAR_QUEUE_H__ */

/******************************************************************************
 * EOF
******************************************************************************/
