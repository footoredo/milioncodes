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

const int N = 5003;
int n, m;
int a[N], t[N], l[N], r[N], k[N], d[N], ta[N];

int main() {
	scanf("%d%d", &n, &m);
	REP(i,n) a[i]=1000000000;
	REP(i,m) { 
    scanf("%d%d%d%d", &t[i], &l[i], &r[i], &k[i]);
    --l[i]; --r[i]; --t[i];
  }
	REP(i,n) REP(j,m) {
		if (i<l[j]||i>r[j]) continue;
		if (t[j]) a[i]=min(a[i], k[j]-d[i]);
		else d[i]+=k[j];
		ta[i]=a[i];
	}
	bool ok=1;
	REP(i,m) if (t[i]) {
		bool tok=0;
		for (int j=l[i]; j<=r[i]; ++j)
			if (ta[j]==k[i]) { tok=1; break; }
		if (!tok) { ok=0; break; }
	}
	else for (int j=l[i]; j<=r[i]; ++j) ta[j]+=k[i];
	if (ok) {
		printf("YES\n");
		REP(i,n) printf("%d ", a[i]);
		printf("\n");
	}
	else printf("NO\n");
	return 0;
}
