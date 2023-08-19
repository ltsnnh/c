#include <stdio.h>
#include "common.h"

#define IN printf
#define N 100

int main()
{
    int M = 200;

    IN("M = %d, N = %d\n", M, N);
    #define M 300
    IN("M = %d, N = %d\n", M, N);
    #undef M
    #define M (N + 400)
    IN("M = %d, N = %d\n", M, N);

    return 0;
}
