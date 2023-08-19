#include <stdio.h>
#include "common.h"

/**
 * Addition             a + b
 * Subtraction          a - b
 * Multiplication       a * b
 * Division             a / b
 * Modulo   a % b
 *
 * Prefix increment     ++a
 * Postfix increment    a++
 * Prefix decrement     --a
 * Postfix decrement    a--
 **/

int main(void)
{
    int a = 0, b = 0, c = 0, d = 0;
    int n = 5;

    printf("result = %d \n", 10 + 2 - 1 * 8 / 2 % 3);
    putchar('\n');

    a = ++n;
    b = n++;
    c = --n;
    d = n--;

    printf("a = %d \tb = %d \tc = %d \td = %d \nn = %d \n", a, b, c, d, n);

    return 0;
}
