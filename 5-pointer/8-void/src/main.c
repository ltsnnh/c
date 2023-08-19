#include <stdio.h>
#include "common.h"

int main(void)
{
    // void a;     /* Error */
    void *p = NULL;

    p = "Ltsnnh";

    puts(p);

    return 0;
}

/**
 * Why type 'void' can be declared for a poiter but not for variable?
 *
 * When a variable is declared in a function, the compiler must allocate a
 * memory space for a variable. But when a variable is of type void, the
 * compiler doesn't know how many bytes to allocate for this variable. So this
 * won't work for the compiler.
 *
 * A pointer can be of type void because it are always stored in a certain
 * amount of memory. It can be read as int or char or float or
 * whatever type...
 *
 * Similarly poiter, also have a function of type void.
 **/
