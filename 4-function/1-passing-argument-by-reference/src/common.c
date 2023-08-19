#include "common.h"

void passing_argument_by_reference(int *pa, int *pb, int *pc, int *pmax)
{
    *pmax = *pa > *pb ? *pa : *pb;
    *pmax = *pmax > *pc ? *pmax : *pc;

    return;
}
