#include <stdio.h>
#include "common.h"

int main(void)
{
    putchar('A');

    putchar('\n');

    puts("HANOI");

    return 0;
}

/**
 * int putchar(char ch);
 *
 * return (true: ch) (false: EOF)
 **/

/**
 * int puts(const char *s);
 *
 * export string s and add '\n' to stdout.
 *
 * return (true: '\n') (false: EOF)
 **/
