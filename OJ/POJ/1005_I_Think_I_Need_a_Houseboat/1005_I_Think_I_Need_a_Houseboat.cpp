#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstdlib>

using namespace std;

const float PI=3.1415926;

int main() {
	int T; scanf("%d", &T);
	for (int i=0; i<T; ++i) {
		float x, y; scanf("%f%f", &x, &y);
		printf("Property %d: This property will begin eroding in year %.0f.\n",
				i+1, (float)ceil(PI*(x*x+y*y)/100.0));
	}
	printf("END OF OUTPUT.\n");
	return 0;
}
