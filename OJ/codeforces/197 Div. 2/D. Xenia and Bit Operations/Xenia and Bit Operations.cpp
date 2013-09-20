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

inline int lowbit(int x) { return x&(-x); }
inline int mgcd(int x, int y) { return y?mgcd(y, x%y):x; }

typedef pair<int, int> Range;
#define lt first
#define rt second
inline bool in(int p, Range r) { return p>=r.lt&&p<=r.rt; }
inline bool in(Range r1, Range r2) { return r1.lt>=r2.lt&&r1.rt<=r2.rt; }
inline int mid(Range rg) { return MID(rg.lt, rg.rt); }
Range shift(bool d, Range rg) {
	return d?Range(mid(rg)+1, rg.rt):Range(rg.lt, mid(rg));
}

int n, m, s;
int tr[500005], a[200005];

bool build(int dep, int x) {
	if (dep==n) { tr[x]=a[x-s]; return 1; }
	bool f=build(dep+1, x<<1); build(dep+1, (x<<1)+1);
	if (f) tr[x]=tr[x<<1]|tr[(x<<1)+1];
	else tr[x]=tr[x<<1]^tr[(x<<1)+1];
	return !f;
}

bool mod(int x, int l, int r, int p, int v) {
	if (l==r) { tr[x]=v; return 1; }
	bool f;
	if (p>(l+r>>1)) f=mod((x<<1)+1,(l+r>>1)+1,r,p,v);
	else f=mod(x<<1,l,l+r>>1,p,v);
	if (f) tr[x]=tr[x<<1]|tr[(x<<1)+1];
	else tr[x]=tr[x<<1]^tr[(x<<1)+1];
	return !f;
}

int main() {
	scanf("%d%d", &n, &m); s=1<<n;
	REP(i,s) scanf("%d", a+i);
	build(0, 1);
	REP(i,m) {
		int p, v;
		scanf("%d%d",&p,&v); --p;
		mod(1,0,s-1,p,v);
		printf("%d\n",tr[1]);
	}
	return 0;
}
