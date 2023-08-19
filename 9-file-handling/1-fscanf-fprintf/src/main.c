#include <stdio.h>
#include <stdlib.h>
#include "common.h"

/* MODE TEXT */

int main(void)
{
    char file1[] = "input.txt";
    char file2[] = "output.txt";
    FILE *fp1 = NULL;
    FILE *fp2 = NULL;
    unsigned char x[10] = {};
    unsigned char y[10] = {};
    unsigned char i = 0;
    unsigned short z[10] = {};
    /* test allocate int in memory */
    unsigned short a = 10335u;
    unsigned char *pa = (unsigned char*)&a;

    /* Open file1 in read text mode */
    fp1 = fopen(file1, "rt");
    if (fp1 == NULL)
    {
        printf("File %s is not existed\n", file1);
        exit(1);
    }

    /* Open file2 in write text mode */
    fp2 = fopen(file2, "wt");
    if (fp2 == NULL)
    {
        printf("File %s can not be created\n", file2);
        exit(1);
    }

    /* Scan - print unsigned char */
    /* Scan from FILE_1 */
    for(i = 0 ; i < 10; i++)
    {
        fscanf(fp1, "%2hhx%2hhx", &x[i], &y[i]);
    }

    /* Print to FILE_2 */
    for(i = 0 ; i < 10; i++)
    {
        fprintf(fp2, "Line %hhu: %2hhx %2hhx\t%hhu %hhu\n", i + 1, x[i], y[i],  x[i], y[i]);
    }

    fputc('\n', fp2);
    rewind(fp1);

    /* Scan - print unsigned short */
    /* Scan from FILE_1 */
    for(i = 0 ; i < 10; i++)
    {
        fscanf(fp1, "%4hx", &z[i]);
    }

    /* Print to FILE_2 */
    for(i = 0 ; i < 10; i++)
    {
        fprintf(fp2, "Line %hhu: %4hx %hd\n", i + 1, z[i], z[i]);
    }

    /* Close 2 files */
    if (fcloseall() != 2)
    {
        printf("fcloseall(void) run incorrectly \n");
    }

    printf("a = %hx = %hd\n", a, a);
    printf("*pa = %hhx\n", *pa);
    printf("*(pa + 1) = %hhx\n", *(pa + 1));

    return 0;
}
