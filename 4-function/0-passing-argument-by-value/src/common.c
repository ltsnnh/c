#include "common.h"

int passing_argument_by_value(int m, int n, int p)
{
    int result = 0;

    result = m > n ? m : n;
    result = result > p ? result : p;

    return(result);
}
