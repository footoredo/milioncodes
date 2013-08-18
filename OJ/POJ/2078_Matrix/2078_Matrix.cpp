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
#define ll first
#define rr second
inline bool in(int p, Range r) { return p>=r.ll&&p<=r.rr; }
inline bool in(Range r1, Range r2) { return r1.ll>=r2.ll&&r1.rr<=r2.rr; }
inline int mid(Range rg) { return MID(rg.ll, rg.rr); }
Range shift(bool d, Range rg) {
	return d?Range(mid(rg)+1, rg.rr):Range(rg.ll, mid(rg));
}

inline int lowbit(int x) { return x&(-x); }
inline int mgcd(int x, int y) { return y?mgcd(y, x%y):x; }

int n, a[10][10], s[10], ans, c[10];

void search(int dep) {
	if (dep==n) {
		int tans=-1000000000, t;
		REP(j, n) GU(c[j], tans);
		SU(tans, ans);
		return;
	}
	else REP(i, n) {
		s[dep]=i; 
		search(dep+1);
		REP(j, n) c[j]=c[j]-a[dep][(j-i+n)%n]+a[dep][(j-i-1+n+n)%n];
	}
	//REP(j, n) c[j]=c[j]-a[dep][(j+1)%n]+a[dep][j];
}

int main() {
	while (scanf("%d", &n), n+1) {
		REP(i, n) REP(j, n) scanf("%d", &a[i][j]);
		REP(j, n) c[j]=0;
		REP(j, n) REP(i, n) {
			c[j]+=a[i][j];
		}
		ans=1000000000; search(0);
		printf("%d\n", ans);
	}
	return 0;
}