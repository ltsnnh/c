#include <stdio.h>
int main()
{
    char * c;
    char ** s;
    char foo[] = "Hello World";

    s = (char**)foo;
    printf("s is %s\n",(char *)s);
    c = (char*)(&s[0]);
    printf("s[0] is %c\n", *c);

    return(0);
}