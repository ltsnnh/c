#include <stdio.h>
#include "common.h"

int main(void)
{
    unsigned int a = 0x1234ABCD;
    unsigned char *c = (unsigned char*)&a;

    /* Little-endian */
    printf("%p = %hhx\n", c, *c);           // 0xCD
    printf("%p = %hhx\n", c + 1, *(c + 1)); // 0xAB
    printf("%p = %hhx\n", c + 2, *(c + 2)); // 0x34
    printf("%p = %hhx\n", c + 3, *(c + 3)); // 0x12

    return 0;
}
