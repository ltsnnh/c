#include <stdio.h>
#include "common.h"

typedef struct {
    char number;
    char* name;
} worker;

worker man[3] = {{7, "mmmm"}, {4, "xxxx"}, {9, "aaaa"}};
worker *pman = man;
worker man_temp;

int main(void)
{
    int i = 0, j = 0;

    for(i = 0; i < 3; i++)
    {
        for(j = i + 1; j < 3; j++)
        {
            if((*(pman + i)).number > (pman + j)->number)
            {
                man_temp = *(pman + i);
                pman[i] = man[j];
                *(pman + j) = man_temp;
            }
        }
    }

    for(i = 0; i < 3; i++)
    {
        printf("%hhd\t", (pman + i)->number);
        puts((*(pman + i)).name);
    }

    return 0;
}
