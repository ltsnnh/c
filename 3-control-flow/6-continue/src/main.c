#include <stdio.h>
#include "common.h"

/**
 * 'continue' works with 'while', 'do-while', 'for'
 **/

int main(void)
{
    int i = 0;

    for(i = 0; i < 10; i++)
    {
        // printf("%d \n", i);
        if(i > 5)
        {
            continue;
        }
        printf("%d \n", i);
    }

    return 0;
}
