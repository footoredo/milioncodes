#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

const int N = 50004;

int p[N], cnt;

int mfind(int x) {
	return x==p[x]?x:(p[x]=mfind(p[x]));
}

void unionset(int x, int y) {
	int fx=mfind(x), fy=mfind(y);
	if (fx==fy) return;
	--cnt;
	p[fy] = fx;
}

int main() {
	int n, m, T=1;
	while (scanf("%d%d", &n, &m), n||m) {
		for (int i=0; i<n; ++i) p[i] = i;
		cnt = n;
		while (m--) {
			int a, b; scanf("%d%d", &a, &b);
			unionset(a, b);
		}
		printf("Case %d: %d\n", T++, cnt);
	}
	return 0;
}
