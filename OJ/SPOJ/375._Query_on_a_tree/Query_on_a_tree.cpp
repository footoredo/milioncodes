#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <iostream>
#include <math.h>
#include <assert.h>
#include <vector>
#include <queue>
#include <string>
#include <map>
#include <set>

using namespace std;
typedef long long ll;
typedef unsigned int uint;
typedef unsigned long long ull;
static const double EPS = 1e-9;
static const double PI = acos(-1.0);
const int N =10004;

#define REP(i, n) for (int i = 0; i < (int)(n); i++)
#define FOR(i, s, n) for (int i = (s); i < (int)(n); i++)
#define FOREQ(i, s, n) for (int i = (s); i <= (int)(n); i++)
#define FORIT(it, c) for (__typeof((c).begin())it = (c).begin(); it != (c).end(); it++)
#define MEMSET(v, h) memset((v), h, sizeof(v))
#define PB push_back
#define GU(a, b) if ((a)>(b)) (b)=(a);
#define SU(a, b) if ((a)<(b)) (b)=(a);

int n, indeg[N];
vector<int> children[N];
int root, a[N], cnt, edges[N];
int d[N];

struct Tree {
	int father, size, weight, dep;
	int hson, top, pos, enumber;
} nodes[N];

void init() {
	FOREQ(i, 1, n)
		indeg[i]=nodes[i].father=nodes[i].size=nodes[i].weight=
			nodes[i].dep=nodes[i].hson=nodes[i].top=d[i]=0;
}

void DFS1(int dep, int x, int fa) {
	nodes[x].father = fa;
	nodes[x].dep = dep;
	nodes[x].size=1;
	nodes[x].hson=children[x].size()?children[x][0]:-1;
	FORIT(it, children[x]) {
		DFS1(dep+1, *it, x);
		nodes[x].size += nodes[*it].size;
		if (nodes[*it].size>nodes[nodes[x].hson].size)
			nodes[x].hson=*it;
	}
}

void DFS2(int x) {
	if (children[x].size()) {
		int y=nodes[x].hson;
		nodes[y].top=nodes[x].top;
		nodes[y].pos=++cnt;
		a[cnt]=nodes[y].weight;
		edges[nodes[y].enumber]=cnt;
		DFS2(nodes[x].hson);
	}
	FORIT(it, children[x])
		if (*it!=nodes[x].hson) {
			nodes[*it].top = *it;
			nodes[*it].pos=++cnt;
			a[cnt]=nodes[*it].weight;
			edges[nodes[*it].enumber]=cnt;
		}
}

inline int lowbit(int x) {
	return x&(-x);
}

void update(int x, int delta) {
	for (; x<n-1; d[x]+=delta, x+=lowbit(x));
}

int _query(int l, int r) {
	int ret=0;
	for (; l<=r;)
		if (r-lowbit(r)+1>=l) {
			ret=max(ret, d[r]);
			r-=lowbit(r);
		}
		else ret=max(ret, a[r--]);
	return ret;
}

int query(int a, int b) {
	int u, v, ret=0;
	while ((u=nodes[a].top)!=(v=nodes[b].top)) {
		if (nodes[u].dep<nodes[v].dep) {
			swap(u, v); swap(a, b);
		}
		ret=max(ret, _query(nodes[u].pos, nodes[a].pos));
		a=u;
	}
	if (a==b) return ret;
	if (nodes[a].dep>nodes[b].dep) swap(a, b);
	return max(ret, _query(nodes[nodes[a].hson].pos, nodes[b].pos));
}

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		init();
		FOR(i, 1, n) {
			int a, b, c; scanf("%d%d%d", &a, &b, &c);
			++indeg[b]; children[a].PB(b);
			nodes[b].weight = c;
			nodes[b].enumber = i;
		}
		FOREQ(i, 1, n)
			if (!indeg[i]) {
				root=i;
				break;
			}
		nodes[root].top=root;
		DFS1(1, root, -1);
		cnt=0;
		DFS2(root);
		FOR(i, 1, n) update(i, a[i]);
		while (1) {
			int x, y;
			char op[10]; scanf("%s", op);
			if (op[0]=='D') break;
			scanf("%d%d", &x, &y);
			if (op[0]=='Q') printf("%d\n", query(x, y));
			else update(edges[x], y-a[x]);
		}
	}
	return 0;
}
