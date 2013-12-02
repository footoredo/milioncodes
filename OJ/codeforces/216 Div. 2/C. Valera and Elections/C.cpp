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

const int N = 200005;
vector<int> adj[N];
bool broken[N], brokene[N];
int x[N], y[N];
vector<int> ans;

bool dfs(int u, int fa) {
	int s=adj[u].size(), v; bool son=0;
//printf("visit %d\n", u);
	REP(i,s) {
		int e=adj[u][i];
		if (x[e]==fa) continue;
		if (y[e]==u) swap(y[e], x[e]);
		if (brokene[e]) broken[y[e]]=1;
		son=dfs(y[e],u)||son;
	}
	if (!son&&broken[u]) {
		ans.push_back(u+1);
	}
	if (son||broken[u]) return 1;
	return 0;
}

int main() {
	int n; scanf("%d", &n);
	REP(i,n-1) {
		int a, b, c; scanf("%d%d%d", &a, &b, &c);
		x[i]=a-1; y[i]=b-1; brokene[i]=c-1;
		adj[x[i]].push_back(i);
		adj[y[i]].push_back(i);
	}
	dfs(0,-1);
	printf("%d\n", ans.size()); int s=ans.size();
	REP(i,s) printf("%d ", ans[i]);
	printf("\n");
	//REP(i,n) printf("%d ", broken[i]);
	//printf("\n");
	return 0;
}
