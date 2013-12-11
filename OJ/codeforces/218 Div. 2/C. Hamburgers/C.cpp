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

const int N = 102;
char recipe[N];
int nd[3], hv[3], p[3];
ll r;

bool check(ll x) {
	ll m=0;
	REP(i,3) if (ll(nd[i])*x>hv[i]) {
		if (r/p[i]<ll(nd[i])*x-hv[i]) return 0;
		m+=(ll(nd[i])*x-hv[i])*p[i];
	}
	return m<=r;
}

int main() {
	scanf("%s", recipe);
	REP(i,strlen(recipe))
		if (recipe[i]=='B') ++nd[0];
		else if (recipe[i]=='S') ++nd[1];
		else ++nd[2];
	REP(i,3) scanf("%d", &hv[i]);
	REP(i,3) scanf("%d", &p[i]);
	cin>>r;
	ll l=0, r=10000000000000LL, mid;
	while (l<r-1) {
		if (check(mid=l+r>>1)) l=mid; else r=mid;
	}
	cout<<l<<endl;
	return 0;
}
