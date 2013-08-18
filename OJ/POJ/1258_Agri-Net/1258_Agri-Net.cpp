#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>

using namespace std;

const int N = 102;

struct Edge {
	int x, y, w;
} E[N*N];

bool cmp(Edge a, Edge b) {
	return a.w<b.w;
}

int n, adj[N][N], ecnt, p[N];

int mfind(int x) {
	if (x!=p[x]) return p[x] = mfind(p[x]);
	else return x;
}

void unionset(int x, int y) {
	int fx = mfind(x),  fy = mfind(y);
	p[fy] = fx;
}

int main() {
	while (scanf("%d", &n) != EOF) {
		ecnt = 0;
		int ans=0;
		for (int i=0; i<n; ++i) {
			p[i] = i;
			for (int j=0; j<n; ++j) {
				scanf("%d", &adj[i][j]);
				E[ecnt].x=i; E[ecnt].y=j;
				E[ecnt++].w=adj[i][j];
			}
		}

		sort(E, E+ecnt, cmp);
		for (int i=0; i<ecnt; ++i)
			if (mfind(E[i].x)!=mfind(E[i].y)) {
				unionset(E[i].x, E[i].y);
				ans += E[i].w;
			}
		printf("%d\n", ans);
	}

	return 0;
}