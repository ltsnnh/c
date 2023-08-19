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
    char buffer[27] = {};
    unsigned char i = 1;

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

    while (!feof(fp1))
    {
        fgets(buffer, 27, fp1);
        fprintf(fp2, "Line %hhu: ", i);
        fputs(buffer, fp2);
        i++;
    }

    /* Close 2 files */
    if (fclose(fp1) == EOF)
    {
        printf("File %s can not be closed\n", file1);
    }
    if (fclose(fp2) == EOF)
    {
        printf("File %s can not be closed\n", file2);
    }

    return 0;
}
