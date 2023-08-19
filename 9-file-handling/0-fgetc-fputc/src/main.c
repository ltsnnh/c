#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "common.h"

int main(void)
{
    char c = 0;
    char file1[27] = {};
    char file2[27] = {};
    FILE *fp1 = NULL;
    FILE *fp2 = NULL;

    /* Get file1_name */
    printf("Source file: ");
    if (fgets(file1, 27, stdin) == NULL)          /* input.txt */
    {
        printf("Fail to read the input stream: file1");
    }
    else
    {
        file1[strcspn(file1, "\n")] = '\0';
    }

    /* Get file2_name */
    printf("Taget file: ");
    if (fgets(file2, 27, stdin) == NULL)          /* output.txt */
    {
        printf("Fail to read the input stream: file2");
    }
    else
    {
        file2[strcspn(file2, "\n")] = '\0';
    }

    /* Open file1 in read binary mode */
    fp1 = fopen(file1, "rb");
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

    /* Copy FILE_1 to FILE_2 in way1*/
    // while ((c = fgetc(fp1)) != EOF)
    // {
    //     fputc(c, fp2);
    // }

    /* Copy FILE_1 to FILE_2 in way2 do not use c variable*/
    while (!feof(fp1))
    {
        fputc(fgetc(fp1), fp2);
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

/* strcspn() returns the number of characters in string1 which are not in the string2. */
