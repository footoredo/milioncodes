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

const int N = 202;

int n, m, l, r;
double p[2][N];

inline int getp(int x) {
	if (x>=n) return x-n;
	if (x<0) return x+n;
	return x;
}

int main() {
	while (scanf("%d%d%d%d",&n,&m,&l,&r),n||m||l||r) {
		bool k=0; --l; --r; double t;
		REP(i, n) { p[0][i]=0; p[1][i]=0;} p[0][0]=1;
		REP(i, m) {
			int w; scanf("%d", &w);
			REP(i, n) {
				p[!k][getp(i-w)]+=t=p[k][i]*0.5;
				p[!k][getp(i+w)]+=t;
				p[k][i]=0;
			}			
			k=!k;
		}
		double ans=0;
		for (int i=l; i<=r; ++i) ans+=p[k][i];
		printf("%.4f\n", ans);
	}
	return 0;
}
