#include <stdio.h>
#include <stdlib.h>
#include "multidimension.h"

/**
 * giong mang nhieu chieu ve cach truy xuat phan tu
 * khac mang nhieu chieu trong cach phan bo bo nho
 **/

void getvalue(int *);

int main(void)
{
    int m = 0, n = 0, k = 0;
    int **pa = NULL, ***pb = NULL;
    int i = 0, j = 0;

    printf("nhap gia tri m = ");
    getvalue(&m);
    printf("nhap gia tri n = ");
    getvalue(&n);
    printf("nhap gia tri k = ");
    getvalue(&k);

    /* cap phat mang nguyen pa 2 chieu kich thuoc m x n */
    /* cap phat dong mang cac con tro cap 1 */
    pa = (int**)malloc(m * sizeof(int *));
    for (i = 0; i < m; i++)
    {
        /* cap phat dong tung con tro cap 1 trong tung mang */
        pa[i] = (int*)malloc(n * sizeof(int));
    }
    /* nhap mang nguyen a 2 chieu kich thuoc m x n */
    nhapmang2chieu(m, n, pa);

    /* cap phat mang nguyen pb 3 chieu kich thuoc m x n x k */
    /* cap phat dong mang cac con tro cap 2 */
    pb = (int***)malloc(m * sizeof(int **));
    for (i = 0; i < m; i++)
    {
        /* cap phat dong mang cac con tro cap 1 */
        pb[i] = (int**)malloc(n * sizeof(int *));
        for(j = 0; j < n; j++)
        {
            /* cap phat dong tung con tro cap 1 trong tung mang */
            pb[i][j] = (int*)malloc(k * sizeof(int));
        }
    }
    /* nhap mang nguyen b 3 chieu kich thuoc m x n x k */
    nhapmang3chieu(m, n, k, pb);

    /* giai phong con tro cap phat dong pa */
    for (i = 0; i < m; i++)
    {
        free(pa[i]);
    }
    free(pa);

    /* giai phong con tro cap phat dong pb */
    for (i = 0; i < m; i++)
    {
        for(j = 0; j < n; j++)
        {
            free(pb[i][j]);
        }
        free(pb[i]);
    }
    free(pb);

    return 0;
}

void getvalue(int *p)
{
    scanf("%d%*c", p);
    while(!((*p > 0) && (*p < 10)))
    {
        printf("nhap lai 0 < x < 10\n");
        scanf("%d%*c", p);
    }

    return;
}
