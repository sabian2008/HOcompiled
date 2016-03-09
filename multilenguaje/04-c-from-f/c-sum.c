#include <stdlib.h>
#include "c-sum.h"

int sum_abs_(int *in, int *num, int *out) {
   int i;

   for (i=0; i < *num; ++i) {
       *out += abs(in[i]);
   }
}
