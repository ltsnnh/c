#include <stdio.h>
#include "common.h"

/**
 * if(expression)
 * {}
 * [else]
 * [{}]
 *
 * expression can be integer or float
 **/

int main(void)
{
    int c =  0, d = 0, max = 0, min = 0;

    printf("Nhap vao 2 so nguyen c, d: ");
    scanf("%d %d%*c", &c, &d);

    if(c > d)
    {
        max = c;
        min = d;
        printf("max = %d \nmin = %d \n", max, min);
    }
    else if(c < d)
    {
        max = d;
        min = c;
        printf("max = %d \nmin = %d \n", max, min);
    }
    else
    {
        max = min = c = d;
        printf("max = min = c = d = %d \n", (c > d) ? c : d);
    }


    return 0;
}
