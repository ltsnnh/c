#include <stdio.h>
#include <stdint.h>
#include "common.h"

#ifdef __GNUC__
#define NOT_ALIGN __attribute__((packed))
#else
#define NOT_ALIGN
#endif

typedef struct
{
    uint8_t a;
    uint32_t b;
    uint16_t c;
} padding_struct_t;

typedef struct
{
    uint8_t a;
    uint32_t b;
    uint16_t c;
} NOT_ALIGN not_padding_struct_t;

int main(void)
{
    padding_struct_t x;
    not_padding_struct_t y;

    printf("sizeof(padding_struct) = %ld\n", sizeof(x));
    printf("sizeof(not_padding_struct) = %ld\n", sizeof(y));

    return 0;
}
