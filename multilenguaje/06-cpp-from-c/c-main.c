
#include <stdio.h>
//#include "c-sum.h"

#define NUM 200

int main(int argc, char **argv)
{
    int data[NUM], num, i;

    num = NUM;
    for (i=0; i < num; i++) {
        data[i] = i - 100 + 1;  /* NOTE: difference in array numbering */
    }

    printf("sum=%d\n", _Z7sum_absPKii(data, num));
    return 0;
}
