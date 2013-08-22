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
inline int mabs(int x) { return x<0?-x:x; }

int n, m;
char gra[50][50];

int main() {
	while (scanf("%d%d", &n, &m), n||m) {
		REP(i, n) {
			getchar();
			REP(j, m) gra[i][j]=getchar();
		}
		int dis=(n+m)*2, aci, acj, ahi, ahj;
		REP(hi, n) REP(hj, m) if(gra[hi][hj]=='H')
		REP(ci, n) REP(cj, m) if(gra[ci][cj]=='C') {
			int tdis=mabs(hi-ci)+mabs(hj-cj);
			if (tdis<dis) {
				dis=tdis;
				aci=ci; acj=cj;
				ahi=hi; ahj=hj;
			}
		}
		printf("%d %d %d %d\n", ahi, ahj, aci, acj);
	}
	return 0;
}
