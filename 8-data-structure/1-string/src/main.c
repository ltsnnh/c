#include <stdio.h>
#include "common.h"

int main(void)
{
    char *ch = NULL, arr1[10] = {}, arr2[10] = {};

    ch = "Ltsnnh";
    puts(ch);

    /* fgets() get '\n' from stdin */
    fgets(arr1, 10, stdin);      /* instead: gets() since C11 */
    puts(arr1);

    /* scanf() leaves '\n' on stdin which to be ignored with %*c */
    scanf("%s%*c", arr2);
    printf("%s\n", arr2);

    return 0;
}
