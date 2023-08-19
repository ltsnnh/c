#include <stdio.h>
#include <limits.h>
#include "common.h"

int main(void)
{
    char ch1 = 0;
    unsigned char ch2 = 0u;

    ch1 = 200;
    ch2 = ch1;

    printf("sizeof(char) (byte) = %ld \n", sizeof(char));   /* 1 */
    printf("sizeof(char) (bit) = %d \n", CHAR_BIT);         /* 8 */

    printf("char max = %d \n", CHAR_MAX);                   /* 127 */
    printf("char min = %d \n", CHAR_MIN);                   /* -128 */
    printf("signed char max = %d \n", SCHAR_MAX);           /* 127 */
    printf("signed char min = %d \n", SCHAR_MIN);           /* -128 */
    printf("unsigned char max = %d \n", UCHAR_MAX);         /* 255 */

    putchar('\n');

    printf("ch1 = %d \n", ch1);                             /* ch2 */
                                                            /* -|2^8 - ch2| */
    printf("ch2 = %d \n", ch2);                             /* ch2 */

    if( 'A' == '\101')
        printf("\'A\' = \'\\101\' = %d \n", 'A');

    return 0;
}
