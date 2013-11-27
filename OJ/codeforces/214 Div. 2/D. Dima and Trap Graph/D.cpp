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

typedef pair<int, int> Range;
#define lt first
#define rt second
inline bool in(int p, Range r) { return p>=r.lt&&p<=r.rt; }
inline bool in(Range r1, Range r2) { return r1.lt>=r2.lt&&r1.rt<=r2.rt; }
inline int mid(Range rg) { return MID(rg.lt, rg.rt); }
Range shift(bool d, Range rg) {
	return d?Range(mid(rg)+1, rg.rt):Range(rg.lt, mid(rg));
}

inline int lowbit(int x) { return x&(-x); }
inline int mgcd(int x, int y) { return y?mgcd(y, x%y):x; }

struct Edge {
	int v, w;
	Edge(int v, int w): v(v), w(w) {}
};

const int N = 1003;
vector<Edge> adj[N*N*2];
vector<int> pool;
int n, m, a[N], b[N], l[N], r[N], si, f[N*N*2], ans=-1;

inline int num(int a, int b) {
	return (a-1)*si+b;
}

void go(int x, int rr) {
	f[x]=rr; int t;
	if (x>=(n-1)*si) {
		if ((t=pool[rr]-pool[(x-(n-1)*si)]+1)>ans)
			ans=t;
		return;
	}
	int s=adj[x].size();
	REP(i,s) {
		Edge &e = adj[x][i];
		int r=min(rr,e.w);
		if (f[e.v]<r) go(e.v,r);
	}
}

int main() {
	scanf("%d%d", &n, &m);
	REP(i,m) {
		scanf("%d%d%d%d", &a[i], &b[i], &l[i], &r[i]);
		pool.push_back(l[i]); pool.push_back(r[i]);
	}
	sort(pool.begin(), pool.end()); si=pool.size();
	REP(i,m) {
		int tl=lower_bound(pool.begin(),pool.end(),l[i])-pool.begin();
		int tr=lower_bound(pool.begin(),pool.end(),r[i])-pool.begin();
		REP(j,tr+1) if (pool[j]<l[i]) {
			adj[num(a[i],j)].push_back(Edge(num(b[i],tl),tr));
			adj[num(b[i],j)].push_back(Edge(num(a[i],tl),tr));
		}
		else {
			adj[num(a[i],j)].push_back(Edge(num(b[i],j),tr));
			adj[num(b[i],j)].push_back(Edge(num(a[i],j),tr));
		}
	}
	REP(i,num(n,si)) f[i]=-1;
	if (m==0) {
	  printf("Nice work, Dima!\n");
	  return 0;
	}
	go(num(1,0), si);
	if (ans<=0) printf("Nice work, Dima!\n");
	else printf("%d\n", ans);

	return 0;
}
