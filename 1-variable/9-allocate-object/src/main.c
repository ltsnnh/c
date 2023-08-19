#include <stdio.h>
#include "common.h"

const int a = 0;
static int c;
static int d = 1;
/* auto int x = 0; */   /* file-scope variable can not be declared by 'auto' */
/* 'auto' is auto add in frond of declaration a local variable */
/* extern y = 0; */     /* do not initializer extern variable */
void function(void);

int main(void)
{
    const int b = 0;
    static int e;
    static int f = 1;
    register int g = 2;
    char *str = "Ltsnnh";

    printf("const a global is allocate at .text: %p\n", &a);
    printf("const b local is allocate at .stack: %p\n", &b);
    /* &a << &b */
    /* .text << .stack */
    putchar('\n');
    printf("static c, e un-initialized is allocate at .bss: %p\t%p\n", &c, &e);
    printf("static d, f initialized is allocate at .data: %p\t%p\n", &d, &f);
    /* &d, &f < &c, &e */
    /* .data < .bss */
    putchar('\n');
    printf("g variable is allocate at register, can not take address of g\n");
    putchar('\n');
    function();
    putchar('\n');
    printf("string is allocate at .text: %p\n", str);
    /* &string near to &(const global variable) */

    return 0;
}

void function(void)
{
    printf("address of function is at .text: %p\n", function);
    /* &funciton < &(const global variable). both at .text */

    return;
}
