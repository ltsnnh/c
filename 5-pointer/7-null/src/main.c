#include <stdio.h>
#include "common.h"

/** The C have
 * a null (NUL) character = 0
 * a pointer null (NULL) does not point to any valid data object
 * a null statement (just a semicolon ';')
 **/

int main(void)
{
    printf("%ld\n",  sizeof(NULL));     /*NULL is a pointer*/

    return 0;
}
