#include <stdio.h>
#include <string.h>
#include "common.h"

int main(void)
{
    char *ch = NULL, arr[10] = {};

    ch = "Ltsnnh";
    // *ch = 'l';      /* Segmentation fault (core dumped) */

    /* Ltsnnh */
    scanf("%s%*c", arr);

    if(strcmp(ch,arr))       /* 0 -> Same | 1 -> Different */
    {
        printf("Different string \n");
    }
    else
    {
        printf("Same string \n");
    }


    *arr = 'l';
    printf("%s \n", arr);

    if(strcmp(ch,arr))       /* 0 -> Same | 1 -> Different */
    {
        printf("Different string \n");
    }
    else
    {
        printf("Same string \n");
    }

    return 0;
}
