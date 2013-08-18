#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

const int N = 30004;

int p[N], nu[N];

int mfind(int x) {
	return x==p[x]?x:(p[x]=mfind(p[x]));
}

void unionset(int x, int y) {
	int fx=mfind(x), fy=mfind(y);
	if (fx==fy) return;
	nu[fx] += nu[fy];
	p[fy] = fx;
}

int main() {
	int n, m;
	while (scanf("%d%d", &n, &m), n||m) {
		for (int i=0; i<n; ++i) { p[i] = i; nu[i] = 1; }
		while (m--) {
			int k, f; scanf("%d%d", &k, &f);
			while (--k) {
				int x; scanf("%d", &x);
				unionset(f, x);
			}
		}
		printf("%d\n", nu[mfind(0)]);
	}
	return 0;
}