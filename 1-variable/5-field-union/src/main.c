#include <stdio.h>
#include "common.h"

/**
 * type of field element: int (unsigned or signed)
 * length max field element: 16 bit
 * not allowed to take address of field element
 * can not get array of field
 * can not return from function{} a field element
 **/

union   /* union */
{
    struct  /* struct */
    {
        unsigned int a1;
        unsigned int a2;
    } s;

    struct  /* field */
    {
        unsigned int n1:16;
        unsigned int:16;
        unsigned int n2:8;
        unsigned int n3:8;
        unsigned int n4:16;
    } f;
} u;

int main(void)
{
    unsigned int a = 0;
    unsigned int b = 0;
    unsigned int c = 0;
    unsigned int d = 0;
    u.s.a1 = 0x0000ACBD;
    u.s.a2 = 0xFCBAD897;
    a = u.f.n1;
    b = u.f.n2;
    c = u.f.n3;
    d = u.f.n4;
    printf("%x\t%x\t%x\t%x\n", a, b, c, d);

    return 0;
}
