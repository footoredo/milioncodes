#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>

using namespace std;

int mgcd(int a, int b) {
	int r;
	while (r=a%b) {
		a = b;
		b = r;
	}
	return b;
}

bool isprime(int x) {
	for (int i=2; i<=sqrt(x); ++i)
		if (x%i==0) return 0;
	return 1;
}

int main() {
	int a, b; scanf("%d%d", &a, &b);
	int c = mgcd(a,b), d = a*b/c, cnt=0;
	for (int i = c+1; i<d; ++i)
		if (isprime(i)) ++cnt;
	printf("I'm confident!%d\n", cnt);
	return 0;
}
