#include <stdio.h>
#include "common.h"

/**
 * char *fgets(char *str, int n, FILE *stream)
 *
 * stop when:   (n - 1) characters is read
 *              meet '\n' ('\n' is ignored from stream and be put to string)
 *              EOF
 *
 * return   true: str
 *          false('EOF and no char be read' or error): NULL
 *
 **/

int main(void)
{
    char name[27];

    fgets(name, 27, stdin);

    puts(name);

    return 0;
}
