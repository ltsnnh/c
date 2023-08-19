#include <stdio.h>
#include <stdlib.h>
#include "common.h"

/* malloc - memory allocate */

int main(void)
{
    int *ptr;
    int i = 0, n = 0;

    printf("Enter number of elements: ");
    scanf("%d%*c", &n);

    ptr = (int*)malloc(n * sizeof(int));

    if(ptr == NULL)
    {
        printf("Error!\n");
    }
    else
    {
        printf("Memory successfully allocated using malloc.\n");
        for(i = 0; i < n; i++)
        {
            *(ptr + i) = i + 1;
        }
        printf("The elements of the array: ");
        for(i = 0; i < n; i++)
        {
            printf("%d\t", *(ptr + i));
        }
        putchar('\n');
    }

    free(ptr);

    return 0;
}
