#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>

using namespace std;

const int N = 1003;

struct Edge {
	int x, y, w;
} E[N*N];

bool cmp(Edge a, Edge b) {
	return a.w<b.w;
}

int p[N];
bool choose[N*N];

int mfind(int x) {
	if (x==p[x]) return x;
	else return p[x]=mfind(p[x]);
}

void unionset(int x, int y) {
	p[mfind(y)]=mfind(x);
}

int main() {
	int n, m; scanf("%d%d", &n, &m);
	for (int i=0; i<m; ++i)
		scanf("%d%d%d", &E[i].x, &E[i].y, &E[i].w);

	sort(E, E+m, cmp);
	for (int i=1; i<=n; ++i) p[i] = i;
	int maxlen;
	for (int k=1, i=0; k<n; ++k) {
		while (mfind(E[i].x)==mfind(E[i].y)) ++i;
		maxlen = E[i].w;
		choose[i] = 1;
		unionset(E[i].x, E[i].y);
	}

	printf("%d\n%d\n", maxlen, n-1);
	for (int i=0; i<m; ++i)
		if (choose[i]) printf("%d %d\n", E[i].x, E[i].y);

	return 0;
}
