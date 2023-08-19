#include <stdio.h>
#include "common.h"

/* MODE BINARY */

int main(void)
{
    FILE *fp;
    int i = 0;

    /* Write to file */
    /* Little endian */
    fp = fopen("medium.txt", "wb");
    for (i = 0; i <= 0xF; i++)
    {
        putw(i, fp);
    }
    fclose(fp);

    /* Read from file, print to screen then */
    fp = fopen("medium.txt", "rb");
    while ((i = getw(fp)) != EOF)
    {
        printf("%x\n", i);
    }
    fclose(fp);

    return 0;
}
