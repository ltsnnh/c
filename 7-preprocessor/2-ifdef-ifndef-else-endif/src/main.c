#include <stdio.h>
#include "common.h"

#define TED 10

int main()
{
#ifdef TED
printf("TED\n");
#else
printf("NO TED\n");
#endif
#ifndef TOP
printf("NO TOP\n");
#endif

return 0;
}
