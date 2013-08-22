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
#define GU(a, b) if ((a)>(b)) (b)=(a)
#define SU(a, b) if ((a)<(b)) (b)=(a)
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
inline double mmax(double x, double y) { return (x<y)?y:x; }

const int M = 200005, N=21;
double f[2][M];
int a[N];
vector<int> divisors[M];

int main() {
	int n; scanf("%d", &n);
	FOREQ(i, 1, n) scanf("%d", &a[i]);
	f[0][1]=0; double t, ans=M;
	FOREQ(i, 2, M) f[1][i]=M;
	bool d=0;
	/*FOREQ(x, 1, M) {
		for (int k=1; k*k<=x; ++k) if (x/k*k==x) {
			divisors[x].PB(k);
			divisors[x].PB(n/k);
		}
	}*/
	FOREQ(i, 1, n) {
		FOREQ(j, 1, M) f[d][j]=M;
		FOREQ(j, 1, M) {
			for (int k=1; k*j<=M; ++k) {
				t=abs(k*j-a[i])*1.0/a[i];
				SU(mmax(f[!d][j], t),f[d][k*j]);
				if (i==n) SU(f[d][k*j], ans);
			}
			/*t=abs(j-a[i])*1.0/a[i];
			//FORIT(it, divisors[j]) SU(mmax(f[!d][*it], t),f[d][j]);
			for (int k=1; k*k<=j; ++k) if (j/k*k==j) {
				SU(mmax(f[!d][k], t),f[d][j]);
				SU(mmax(f[!d][j/k], t), f[d][j]);
			}
			if (i==n) SU(f[d][j], ans);*/
			
		}
		d=!d;
	}
	printf("%.10f\n", ans);
	return 0;
}
