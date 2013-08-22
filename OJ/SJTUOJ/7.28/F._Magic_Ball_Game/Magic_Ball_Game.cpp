#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <string>
#include <vector>

using namespace std;

typedef long long ll;

const int N = 500005;

inline int lowbit(int x) {
	return x&(-x);
}

int mmax, cnt[N], ld[N], rd[N], lc[N], rc[N], ans2[N], ans7[N], g[N];
vector<int> query[N], pos[N];

void modify(int *d, int p, int delta) {
	for (; p<=mmax; d[p]+=delta, p+=lowbit(p));
}

int _sum(int *d, int p) {
	int ret=0;
	for (; p; ret+=d[p], p-=lowbit(p));
	return ret;
}

int sum(int *d, int l, int r) {
	return _sum(d, r)-_sum(d, l-1);
}

void DFS(int x) {
	for (int i=0; i<cnt[x]; ++i) {
		int m=query[x][i], p=pos[x][i];
		if (sum(ld, m, m)||sum(rd, m, m)) {
			ans2[p]=-1; continue;
		}
		ans2[p]=sum(ld, 1, m-1)*3+sum(rd, 1, m-1)*3
			+sum(ld, m+1, mmax)+sum(rd, m+1, mmax);
		ans7[p]=sum(rd, 1, m-1);
	}
	if (!lc[x]) return;
	modify(ld, g[x], 1);
	DFS(lc[x]);
	modify(ld, g[x], -1);
	modify(rd, g[x], 1);
	DFS(rc[x]);
	modify(rd, g[x], -1);
}

vector<int> hash;

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		hash.clear();
		int n; scanf("%d", &n);
		memset(ld, 0, sizeof ld);
		memset(rd, 0, sizeof rd);
		for (int i=1; i<=n; ++i) {
			scanf("%d", &g[i]);
			hash.push_back(g[i]);
			lc[i]=rc[i]=0;
			cnt[i]=0;
			query[i].clear();
			pos[i].clear();
		}
		int m; scanf("%d",&m);
		while (m--) {
			int u, a, b;
			scanf("%d%d%d", &u, &a, &b);
			lc[u]=a; rc[u]=b;
		}
		int q; scanf("%d", &q);
		for (int i=0; i<q; ++i) {
			int v, x; scanf("%d%d", &v, &x);
			query[v].push_back(x);
			pos[v].push_back(i);
			++cnt[v];
			hash.push_back(x);
		}
		sort(hash.begin(), hash.end());
		for (int i=1; i<=n; ++i) {
			g[i]=lower_bound(hash.begin(), hash.end(), g[i])-hash.begin()+1;
			if (g[i]>mmax) mmax=g[i];
			for (int j=0; j<cnt[i]; ++j) {
				query[i][j]=lower_bound(hash.begin(), hash.end(), query[i][j])-hash.begin()+1;
				if (query[i][j]>mmax) mmax=query[i][j];
			}
		}
		DFS(1);
		for (int i=0; i<q; ++i)
			if (ans2[i]==-1) printf("0\n");
			else printf("%d %d\n", ans7[i], ans2[i]);
	}
	return 0;
}
