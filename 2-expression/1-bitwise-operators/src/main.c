#include <stdio.h>
#include "common.h"

/** Bitwise operators
 * AND  a & b
 * OR   a | b
 * XOR  a ^ b
 * NOT  ~a
 **/

/** Bit shifts
 * Arithmetic shift (int)
 * Logical shifts   (unsigned int)
 *
 * Left shifts      A << n
 * Right shifts     A >> n
 **/

int main(void)
{
    unsigned short a = 0xA1B6;
    unsigned short f[6] = {};

    f[0] = a & 0xFF;
    f[1] = a | 0xFF;
    f[2] = a ^ a;
    f[3] = a << 8;
    f[4] = a >> 8;
    f[5] = ~a;

    for(int i = 0; i < 6; i++)
    {
        printf("f[%d] = %04x \n", i, f[i]);
    }

    return 0;
}
