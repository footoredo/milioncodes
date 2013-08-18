#include <iostream>
#include <cmath>
#include <cstdio>

using namespace std;

const double zero = 0.00000001;

int main() {
	double x;
	while (scanf("%lf", &x), abs(x)>zero) {
		int n=1;
		double t = 0;
		while (t<x) t+=1.0/(++n);
		printf("%d card(s)\n", n-1);
	}
	return 0;
}
