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

const int N = 2003;
int n, k;
int a[N], f[N];

bool check(ll x) {
	if (x==-1) return 0;
	REP(i,n) {
		f[i]=i;
		REP(j,i) if (abs(a[i]-a[j])<=x*(i-j))
			f[i]=min(f[i],f[j]+i-j-1);
	}
	int ans=n;
	REP(i,n) if (f[i]+n-i-1<ans) ans=f[i]+n-i-1;
	return ans<=k;
}

int main() {
	scanf("%d%d", &n, &k);
	REP(i,n) scanf("%d", &a[i]);
	ll l=-1, r=2000000000, mid;
	while (l+1<r) {
		if (check(mid=l+r>>1))
			r=mid;
		else l=mid;
	}
	printf("%I64d\n", r);
	return 0;
}
