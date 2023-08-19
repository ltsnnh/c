#include <stdio.h>
#include "common.h"

#define  message_for(a,b)  \
    printf(#a " and " #b ": Have a nice day!\n");

int main(void)
{
    message_for(Tuan, Hang)

    return 0;
}
