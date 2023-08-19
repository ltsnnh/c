#include <stdio.h>
#include "common.h"

/**
 * 'break' works with 'switch-case', 'while', 'do-while', 'for'
 **/

int main(void)
{
    int i = 0;

    for(i = 0; i < 10; i++)
    {
        printf("%d \n", i);
        if(i == 5)
        {
            break;
        }
    }

    return 0;
}
