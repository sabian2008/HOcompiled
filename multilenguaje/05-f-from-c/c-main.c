
#include <stdio.h>
//#include "c-sum.h"

#define NUM 200

int main(int argc, char **argv)
{
    int i;
    int data[NUM];
    int num;
    int out;

    out = 0;
    num = NUM;
    for (i=0; i < num; i++) {
        data[i] = i - 100 + 1;  /* NOTE: difference in array numbering */
    }

    sum_abs_(data, &num, &out);

    printf("sum=%d\n", out);
    return 0;
}
