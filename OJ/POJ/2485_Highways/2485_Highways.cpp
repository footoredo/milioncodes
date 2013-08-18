#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 502;

struct Edge {
	int u, v, w;
} edge[N*N];

bool cmp(Edge a, Edge b) {
	return a.w<b.w;
}

int p[N], n;

int mfind(int x) {
	return p[x]==x?x:(p[x]=mfind(p[x]));
}

void unionset(int x, int y) {
	int fx = mfind(x), fy = mfind(y);
	p[fx] = fy;
}

int main() {
	int T, m; scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		m = 0;
		for (int i=1; i<=n; ++i)
			for (int j=1; j<=n; ++j) {
				int x; scanf("%d", &x);
				edge[m].u = i; edge[m].v = j; edge[m++].w = x;
			}
		for (int i=1; i<=n; ++i) p[i] = i;

		int ans;
		sort(edge, edge+m, cmp);
		for (int cnt=1, i=0; cnt<n; ++cnt) {
			while (mfind(edge[i].u)==mfind(edge[i].v)) ++i;
			ans = edge[i].w;
			unionset(edge[i].u, edge[i].v);
		}

		printf("%d\n", ans);
	}
	return 0;
}
/*
1

3
0 990 692
990 0 179
692 179 0
*/
