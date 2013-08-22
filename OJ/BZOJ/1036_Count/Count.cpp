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

#define REP(i, n) for (int i = 0; i < (int)(n); i++)
#define FOR(i, s, n) for (int i = (s); i < (int)(n); i++)
#define FOREQ(i, s, n) for (int i = (s); i <= (int)(n); i++)
#define FORIT(it, c) for (__typeof((c).begin())it = (c).begin(); it != (c).end(); it++)
#define MEMSET(v, h) memset((v), h, sizeof(v))
#define PB push_back
#define GU(a, b) if ((a)>(b)) (b)=(a);
#define SU(a, b) if ((a)<(b)) (b)=(a);
#define MID(l, r) (((l)+(r))>>1)
#define SZ(a) a.size()

typedef pair<int, int> Range;
#define ll first
#define rr second
inline int mid(Range rg) { return MID(rg.ll, rg.rr); }
inline bool in(int p, Range r) { return p>=r.ll&&p<=r.rr; }
inline bool in(Range r1, Range r2) { return r1.ll>=r2.ll&&r1.rr<=r2.rr; }
Range shift(bool d, Range rg) {
	return d?Range(mid(rg)+1, rg.rr):Range(rg.ll, mid(rg));
}

inline int lowbit(int x) { return x&(-x); }
inline int mgcd(int x, int y) { return y?mgcd(y, x%y):x; }

const int N = 30004*4;

struct STree {
	Range rg;
	int maxi, sum, ch[2];
	inline void _init(Range rg) { this->rg=rg; maxi=-0x7fffffff; sum=ch[0]=ch[1]=0; }
	inline void _update();
} ST[N];

int mem=1, root;

inline void STree::_update() {
	if (rg.ll<rg.rr) {
		maxi=max(ST[ch[0]].maxi, ST[ch[1]].maxi);
		sum=ST[ch[0]].sum+ST[ch[1]].sum;
	}
}

void buildST(int &x, Range rg) {
	x=mem++; ST[x]._init(rg);
	if (rg.ll<rg.rr) REP(d, 2) buildST(ST[x].ch[d], shift(d,rg));
}

void _modify(int x, int p, int val) {
	STree &t=ST[x];
	if (t.rg.ll<t.rg.rr) REP(d, 2)
		if (in(p, shift(d, t.rg))) _modify(t.ch[d], p, val);
	else { t.maxi+=val; t.sum+=val; }
	t._update();
}

int _querymax(int x, Range rg) {
	STree &t=ST[x]; int ret=-0x7fffffff;
	if (in(t.rg, rg)) t.maxi; int r[2]={rg.ll, rg.rr};
	REP(d, 2) if (in(r[d], ST[t.ch[d]].rg))
		ret=max(_querymax(t.ch[d], rg), ret);
	return ret;
}

int _querysum(int x, Range rg) {
	STree &t=ST[x]; int ret=0;
	if (in(t.rg, rg)) t.sum; int r[2]={rg.ll, rg.rr};
	REP(d, 2) if (in(r[d], ST[t.ch[d]].rg))
		ret+=_querysum(t.ch[d], rg);
	return ret;
}

struct Tree {
	int w, hson, pos, top, fa, dep, size;
	vector<int> ch;
} T[N];

bool vis[N];
vector<int> adj[N];
int cnt=1;
void buildT(int x, int fa, int dep) {
	T[x].fa=fa; T[x].dep=dep; T[x].size=1; T[x].hson=0; vis[x]=1;
	int tcnt=0, tp=0;
	FORIT(it, adj[x]) if (!vis[*it]) {
		T[x].ch.PB(*it); buildT(*it, x, dep+1);
		T[x].size+=T[*it].size;
		if (!T[x].hson||T[*it].size>T[T[x].hson].size) {
			T[x].hson=*it;
			tp=tcnt;
		} ++tcnt;
	} if (SZ(T[x].ch)) swap(T[x].ch[0], T[x].ch[tp]);
}

void chain(int x, int fa) {
	T[x].top=x==T[fa].hson?T[fa].top:fa;
	_modify(root, T[x].pos=cnt++, T[x].w);
	FORIT(it, T[x].ch) chain(*it, x);
}

int querymax(int u, int v) {
	int tu, tv, ret=-0x7fffffff;
	while ((tu=T[u].top)!=(tv=T[v].top)) {
		if (T[tu].dep<T[tv].dep) { swap(tu, tv); swap(u, v); }
		ret=max(ret, _querymax(root, Range(T[u=T[tu].fa].pos, T[u].pos)));
	}
	if (T[u].dep<T[v].dep) swap(u, v);
	return max(ret, _querymax(root, Range(T[v].pos, T[u].pos)));
}

int querysum(int u, int v) {
	int tu, tv, ret=0;
	while ((tu=T[u].top)!=(tv=T[v].top)) {
		if (T[tu].dep<T[tv].dep) { swap(tu, tv); swap(u, v); }
		ret+=_querysum(root, Range(T[u=T[tu].fa].pos, T[u].pos));
	}
	if (T[u].dep<T[v].dep) swap(u, v);
	return ret+_querysum(root, Range(T[v].pos, T[u].pos));
}

inline void modify(int u, int val) { return _modify(root, T[u].pos, val); }

int main() {
	int n; scanf("%d", &n);
	REP(i, n-1) {
		int x, y; scanf("%d%d", &x, &y);
		adj[x].PB(y); adj[y].PB(x);
	}
	buildT(1, 0, 1); buildST(root, Range(1, n));
	FOREQ(i, 1, n) scanf("%d", &T[i].w);
	int m; scanf("%d", &m);
	while (m--) {
		int x, y; char op[5]; scanf("%s%d%d", op, &x, &y);
		switch (op[1]) {
			case 'H': modify(x, y); break;
			case 'M': printf("%d\n", querymax(x, y)); break;
			case 'S': printf("%d\n", querysum(x, y)); break;
		}
	}
	return 0;
}
/*
4
1 2
2 3
4 1
4 2 1 3
12
QMAX 3 4
QMAX 3 3
QMAX 3 2
QMAX 2 3
QSUM 3 4
QSUM 2 1
CHANGE 1 5
QMAX 3 4
CHANGE 3 6
QMAX 3 4
QMAX 2 4
QSUM 3 4
*/
