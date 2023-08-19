#include <stdio.h>
#include "common.h"

#define MAX 276

int main()
{
    #if MAX < 100               /* const expression */
    printf("Bien dich voi MAX < 100\n");
    #elif MAX < 200             /* const expression */
    printf("Bien dich voi MAX < 200\n");
    #elif MAX < 300             /* const expression */
    printf("Bien dich voi MAX < 300\n");
    #elif MAX < 400             /* const expression */
    printf("Bien dich voi MAX < 400\n");
    #elif MAX < 500             /* const expression */
    printf("Bien dich voi MAX < 500\n");
    #else
    printf("Bien dich voi MAX >= 500\n");
    #endif

    return 0;
}
