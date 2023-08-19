#include <stdio.h>
#include "common.h"

/**
 * LABEL:
 *
 * goto LABEL;
 *
 * can only jump in a function
 * can not jump from outside to inside of command block {}
 * vice versa can do
 **/

int main(void)
{
    int a = 0, b = 0;

    tt:
    printf("Nhap 2 so a, b sao cho a > b \na = ");
    scanf("%d%*c", &a);
    printf("b = ");
    scanf("%d%*c", &b);
    if(a > b)
        printf("Done! \n");
    else
        goto tt;

    return 0;
}
