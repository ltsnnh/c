#include <stdio.h>
#include "common.h"

/**
 * (type)a
 **/

int main(void)
{
    unsigned short a = 0xADBC;

    printf("%hhx \n", (unsigned char)a);

    return 0;
}
