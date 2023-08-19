#include <stdio.h>
#include "common.h"

#define MAX(A,B) (A)>(B)?(A):(B)

int main()
{
    int m = 5, n = 8;

    printf("%d\n", MAX(m,n));

    return 0;
}
