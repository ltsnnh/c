#include <stdio.h>
#include "common.h"

int main(void)
{
    char ch[10] = {};

    gets(ch);

    printf("ch = %s \n", ch);

    return 0;
}

/**
 * char *gets(char *s);
 *
 * the 'gets' function is dangerous and should not be used
 *
 * get characters from stdin until get '\n'
 * '\n' is ignored from stdin but not to be put to string
 * add '\0' to end of string
 *
 * return: address of the received string
 **/
