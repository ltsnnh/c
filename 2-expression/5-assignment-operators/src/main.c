#include <stdio.h>
#include "common.h"

/** Assignment operator
 * v = e
 *
 * return: value of e, type of v
 **/

/**
 * Direct assignment            a = b
 * Addition assignment          a += b
 * Subtraction assignment       a -= b
 * Multiplication assignment    a *= b
 * Division assignment          a /= b
 * Modulo assignment            a %= b
 *
 * Bitwise AND assignment           a &= b
 * Bitwise OR assignment            a |= b
 * Bitwise XOR assignment           a ^= b
 * Bitwise left shift assignment    a <<= b
 * Bitwise right shift assignment   a >>= b
 **/


int main(void)
{
    int x = 0, y = 0, z = 0;

    z = (x = 6) * (y = 2);

    printf("z = %d \n", z);

    return 0;
}
