#include <stdio.h>
#include "common.h"

int main(void)
{
    char m = 0;
    char ch[10] = {};

    /* abcd n */
    scanf("%s%*c", ch);
    // scanf("%s ", ch);
    // scanf("%s %*c", ch);

    m = getchar();

    printf("m = %c \n", m);

    return 0;
}

/**
 * int getchar(void);
 *
 * return: received characters
 **/
