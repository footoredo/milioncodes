#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#define CU(x) ((x)*(x)*(x))
using namespace std;

int main() {
  int n; scanf("%d", &n);
  int a=6, b, c, d;
  while ( a<=n ) {
    int t = CU(a);
    for (b=2; b<a; ++b)
      for (c=b; c<a; ++c)
	for (d=c; d<a; ++d)
	  if (CU(b)+CU(c)+CU(d)==t) {
	    printf("Cube = %d, Triple = (%d,%d,%d)\n", a,b,c,d);
	    break;
	  }
	  else if (CU(b)+CU(c)+CU(d)>t) break;
    ++a;
  }
  return 0;
}