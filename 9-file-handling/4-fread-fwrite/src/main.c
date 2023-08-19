#include <stdio.h>
#include "common.h"

/* MODE BINARY */

int main(void)
{
    int n = 0;
    int i = 0;
    int arr[10] = {};
    char *pc = (char*)arr;
    FILE *f1, *f2;

    f1 = fopen("input.txt", "rb");
    f2 = fopen("output.txt", "wb");

    n = fread(arr, 4, 1, f1);

    for (i = 0; i < 4; i++)
    {
        printf("pc[%d] = %hhd\n", i, *(pc+i));
    }

    fwrite(arr, 4, n, f2);
    fputc('\n', f2);

    fclose(f1);
    fclose(f2);

    return 0;
}
