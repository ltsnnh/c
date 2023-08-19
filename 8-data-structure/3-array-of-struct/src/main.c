#include <stdio.h>
#include "common.h"

typedef struct {
    char number;
    char* name;
} worker;

worker man[3] = {{7, "mmmm"}, {4, "xxxx"}, {9, "aaaa"}};
worker man_temp;

int main(void)
{
    int i = 0, j = 0;

    for(i = 0; i < 3; i++)
    {
        for(j = i + 1; j < 3; j++)
        {
            if(man[i].number > man[j].number)
            {
                man_temp = man[i];
                man[i] = man[j];
                man[j] = man_temp;
            }
        }
    }

    for(i = 0; i < 3; i++)
    {
        printf("%hhd\t", man[i].number);
        puts(man[i].name);
    }

    return 0;
}
