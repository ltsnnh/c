#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "common.h"

typedef struct node
{
    uint8_t data;
    struct node *pNext;
} node_t;

node_t* head = NULL;

int main(void)
{
    head->pNext = NULL;

    return 0;
}
