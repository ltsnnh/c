#include <stdio.h>
#include "common.h"

float operation(int a, int b, float (*callback)(int, int));
float add(int a, int b);
float subtract(int a, int b);
float multiply(int a, int b);
float divide(int a, int b);

int main(void)
{
    printf("%.3f\n", operation(5, 2, add));
    printf("%.3f\n", operation(5, 2, subtract));
    printf("%.3f\n", operation(5, 2, multiply));
    printf("%.3f\n", operation(5, 2, divide));

    return 0;
}

float operation(int a, int b, float (*callback)(int, int))
{
    return (*callback)(a, b);
}

float add(int a, int b)
{
    return (a + b);
}

float subtract(int a, int b)
{
    return (a - b);
}

float multiply(int a, int b)
{
    return (a * b);
}

float divide(int a, int b)
{
    return ((float)a / b);
}

