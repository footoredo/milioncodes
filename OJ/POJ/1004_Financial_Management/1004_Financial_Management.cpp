#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

float sum=0;

int main() {
	for (int i=0; i<12; ++i) {
		float x; scanf("%f", &x);
		sum += x;
	}
	printf("$%.2f\n", sum/12.0);
	return 0;
}
