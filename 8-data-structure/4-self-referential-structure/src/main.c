#include <stdio.h>
#include <stdint.h>
#include "common.h"

/*  // Typedef 1
struct node
{
    char name[27];
    uint8_t age;
    struct node *pNext;
};
typedef struct node node_t;
*/

/*  // Typedef 2
typedef struct node node_t;
struct node
{
    char name[27];
    uint8_t age;
    node_t *pNext;
};
*/

    // Typedef 3
typedef struct node
{
    char name[27];
    uint8_t age;
    struct node *pNext;
} node_t;

int main(void)
{
    node_t node1 = {"Ltsnnh", 25, NULL};

    printf("My name is %s\n", node1.name);
    printf("My age is %hhu\n", node1.age);

    return 0;
}
