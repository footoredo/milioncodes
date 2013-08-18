#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

const int N = 1000006;

bool isprime[N];
int primes[N], cnt=0;

void seive(int size) {
	for (int i=2; i<=size; ++i) isprime[i] = 1;
	for (int i=2; i<=size; ++i) {
		if (isprime[i]) primes[cnt++]=i;
		for (int j=0; primes[j]&&i*primes[j]<=size; ++j) {
			isprime[i*primes[j]] = 0;
			if (i%primes[j]==0) break;
		}
	}
}

int main() {
	seive(N);
	int x;
	while (scanf("%d", &x), x) {
		for (int i=1; ; ++i)
			if ((primes[i]&1)&&isprime[x-primes[i]]){
				printf("%d = %d + %d\n", x, primes[i], x-primes[i]);
				break;
			}
	}
	return 0;
}
