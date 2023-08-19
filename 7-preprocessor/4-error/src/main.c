#include <stdio.h>
#include "common.h"

#define VAR 100
#define MAX 200

int main()
{
    #if VAR > MAX
    #error MAX too small. Make it bigger and recompile
    #endif

    return 0;
}
