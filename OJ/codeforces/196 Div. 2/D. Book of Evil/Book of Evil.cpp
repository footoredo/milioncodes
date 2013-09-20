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
const int N = 100005;

#define REP(i, n) for (int i = 0; i < (int)(n); i++)
#define FOR(i, s, n) for (int i = (s); i < (int)(n); i++)
#define FOREQ(i, s, n) for (int i = (s); i <= (int)(n); i++)
#define FORIT(it, c) for (__typeof((c).begin())it = (c).begin(); it != (c).end(); it++)
#define MEMSET(v, h) memset((v), h, sizeof(v))
#define PB push_back
#define GU(a, b) if ((a)>(b)) (b)=(a);
#define SU(a, b) if ((a)<(b)) (b)=(a);
#define MID(l, r) (((l)+(r))>>1)

inline int lowbit(int x) { return x&(-x); }
inline int mgcd(int x, int y) { return y?mgcd(y, x%y):x; }

int d[N], u[N], td[N], gs[N];
vector<int> adj[N];
int n, m, D, x, y, ans=0;

void dfsd(int x, int fa) {
	FORIT(it,adj[x]) if (fa!=*it) {
		dfsd(*it,x); if (d[*it]>=d[x]) {
			d[x]=d[*it]+1; gs[x]=*it;
		}
	}
	FORIT(it,adj[x]) if (*it!=gs[x]&&d[*it]>=td[x]) td[x]=d[*it]+1;
}

void dfsu(int x, int fa) {
	if (fa!=-1) u[x]=max(u[fa],x==gs[fa]?td[fa]:d[fa])+1;
	FORIT(it,adj[x]) if (fa!=*it) dfsu(*it, x);
}

int main() {
	scanf("%d%d%d", &n, &m, &D);
	REP(i,n) d[i]=u[i]=td[i]=-N-N;
	REP(i,m) { scanf("%d", &x); d[x-1]=u[x-1]=0; }
	REP(i,n-1) {
		scanf("%d%d", &x, &y); --x; --y;
		adj[x].PB(y); adj[y].PB(x);
	}
	dfsd(0,-1); dfsu(0,-1);
	REP(i,n) if (max(u[i],d[i])<=D) ++ans;
	printf("%d\n", ans);

	return 0;
}
