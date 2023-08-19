#include <stdio.h>
#include <stdint.h>

typedef struct ll
{
    uint8_t integer;
    struct ll *pNext;
} linkedList_t;

linkedList_t* pHead = NULL;

int main(void)
{
    linkedList_t node[5] = {
        {3, NULL}, {5, NULL}, {4, NULL}, {2, NULL}, {1, NULL}
    };
    int i = 0;
    linkedList_t* pCurrent = NULL;

    pHead = node;
    for (i = 0; i < 5; i++)
    {
        node[i].pNext = &node[i + 1];
        if ( i == 4)
        {
            node[i].pNext = NULL;
        }
    }

    node[0].pNext = &node[1];

    for (pCurrent = pHead; pCurrent != NULL; pCurrent = pCurrent->pNext)
    {
        printf("%hhu\n", pCurrent->integer);
    }

    return 0;
}
