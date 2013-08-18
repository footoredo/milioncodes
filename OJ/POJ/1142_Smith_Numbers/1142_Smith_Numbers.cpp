#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>

using namespace std;

int solve(int x) {
	int ret = 0;
	while (x) { ret += x%10; x /= 10; }
	return ret;
}

int main() {
	int x;
	while (scanf("%d", &x), x) {
		//printf("%d\n", x);
		for (int i=x+1; ; ++i) {
			int t = i, cnt = solve(t);
			//printf("%d\n", i);
			bool isprime = 1;
			for (int j=2; j<=sqrt(t); ++j)
				if (t%j==0) {
					t/=j;
					isprime = 0;
					cnt -= solve(j--);
				}
			cnt -= solve(t);
			if (!cnt&&!isprime) {
				printf("%d\n", i);
				break;
			}
		}
	}
	return 0;
}
