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
	int m;
	while (scanf("%d", &n), n) {
		m = 0;
		for (int i=1; i<n; ++i) {
			int k, u; char v[5];
			scanf("%s%d", v, &k);
			u = v[0]-'A'+1;
			while (k--) {
				int x; scanf("%s%d", v, &x);
				edge[m].u = u; edge[m].v = v[0]-'A'+1; edge[m++].w = x;
			}
		}
		for (int i=1; i<=n; ++i) p[i] = i;

		int ans=0;
		sort(edge, edge+m, cmp);
		for (int cnt=1, i=0; cnt<n; ++cnt) {
			while (mfind(edge[i].u)==mfind(edge[i].v)) ++i;
			ans += edge[i].w;
			unionset(edge[i].u, edge[i].v);
		}

		printf("%d\n", ans);
	}
	return 0;
}
/*
9
A 2 B 12 I 25
B 3 C 10 H 40 I 8
C 2 D 18 G 55
D 1 E 44
E 2 F 60 G 38
F 0
G 1 H 35
H 1 I 35
3
A 2 B 10 C 40
B 1 C 20
0
*/
