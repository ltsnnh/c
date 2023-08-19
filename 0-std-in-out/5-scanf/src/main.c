#include <stdio.h>
#include "common.h"

int main(void)
{
    char a = 0;
    char ch[10] = {};

    /* abcd<ENTER>e */

    scanf("%s%*c", ch);
    scanf("%c", &a);

    if(a == '\n')
    {
        printf("a = \\n \n");
    }
    else
    {
        printf("a = %c \n", a);
    }

    return 0;
}
