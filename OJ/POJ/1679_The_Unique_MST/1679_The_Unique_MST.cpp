#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 102;

struct Edge {
	int u, v, w;
} edge[N*N];

bool cmp(Edge a, Edge b) {
	return a.w<b.w;
}

int p[N], n;
bool vis[N], map[N][N];

int mfind(int x) {
	return p[x]==x?x:(p[x]=mfind(p[x]));
}

void unionset(int x, int y) {
	int fx = mfind(x), fy = mfind(y);
	p[fx] = fy;
}

void go(int u) {
	vis[u] = 1;
	for (int v=1; v<=n; ++v)
		if (map[u][v]&&!vis[v])
			go(v);
}

int main() {
	int T, m; scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &m);
		for (int i=0; i<m; ++i) {
			scanf("%d%d%d", &edge[i].u, &edge[i].v, &edge[i].w);
			map[edge[i].u][edge[i].v] = map[edge[i].v][edge[i].u] = 1;
		}
		memset(vis, 0, sizeof vis);
		go(1); bool connected = 1;
		for (int i=1; i<=n; ++i) connected=connected&&vis[i];
		if (!connected) {
			printf("0\n");
			continue;
		}
		for (int i=1; i<=n; ++i) p[i] = i;

		int ans = 0, last = -1, fu, fv;
		sort(edge, edge+m, cmp);
		for (int cnt=1, i=0; cnt<n; ++cnt) {
			while ((fu=mfind(edge[i].u))==(fv=mfind(edge[i].v))) ++i;
			for (int j=i+1; edge[j].w==edge[i].w; ++j)
				if ((mfind(edge[j].u)==fu)&&(mfind(edge[j].v)==fv)
					||(mfind(edge[j].u)==fv)&&(mfind(edge[j].v)==fu)) { ans = -1; break; }
			if (!(ans+1)) break;
			ans += last = edge[i].w;
			unionset(edge[i].u, edge[i].v);
		}

		if (ans+1) printf("%d\n", ans);
		else printf("Not Unique!\n");
	}
	return 0;
}
/*
2
3 3
1 2 1
2 3 2
3 1 3
4 4
1 2 2
2 3 2
3 4 2
4 1 2
*/
