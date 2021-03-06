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

const int N = 100005;

struct Target {
	int xl, xr, yl, yr, z, order;
} t[N];

bool cmp(Target a, Target b) {
	return a.z<b.z;
}

bool off[N];
int prev[N], succ[N];

int main() {
	int n; scanf("%d", &n);
	REP(i, n) {
		scanf("%d%d%d%d%d", &t[i].xl, &t[i].xr, &t[i].yl, &t[i].yr, &t[i].z);
		t[i].order = i+1;
		prev[i]=i-1; succ[i]=i+1;
	}
	int m, first = 0; scanf("%d", &m);
	sort(t, t+n, cmp);
	REP(i, m) {
		int x, y, ans=0; scanf("%d%d", &x, &y);
		for (int j=first; j<n; j=succ[j]) 
			if ((x>=t[j].xl&&x<=t[j].xr)&&(y>=t[j].yl&&y<=t[j].yr)) { ans=j+1; break; }
		if (!ans) printf("0\n"); 
		else {
			printf("%d\n", t[--ans].order);
			if (ans==first) {
				first = succ[ans];
				prev[succ[ans]]=-1;
			}
			else {
				prev[succ[ans]]=prev[ans];
				succ[prev[ans]]=succ[ans];
			}
		}
	}
	return 0;
}
