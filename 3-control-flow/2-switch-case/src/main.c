#include <stdio.h>
#include "common.h"

/**
 * switch(integer expression)
 * {
 *    case n1:
 *    {}
 *    case n2:
 *    {}
 *
 *
 *    [default:
 *    {}]
 * }
 **/

enum {a, b, c, d, e, f};

int main(void)
{
    switch(2)
    {
        case a:
        printf("a = %d \n", 0);
        break;
        case b:
        printf("b = %d \n", 1);
        break;
        case c: /* case without break(); */
        printf("c = %d \n", 2);
        case d:
        printf("d = %d \n", 3);
        break;
        case e:
        printf("e = %d \n", 4);
        break;
        case f:
        printf("f = %d \n", 5);
        break;
        default:
        break;
    }

    return 0;
}
