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
int n, k;
int a[N], b[N], c[N];
int f[N][20*N*N], SH=10*N*N;

int main() {
	scanf("%d%d", &n, &k);
	REP(i,n) scanf("%d", &a[i+1]);
	REP(i,n) scanf("%d", &b[i+1]);
	REP(i,n) {
		c[i+1]=a[i+1]-b[i+1]*k;
	}
	REP(i,SH*2) f[0][i]=-1;
	f[0][SH]=0;
	for (int i=1; i<=n; ++i)
		REP(j,SH*2) {
			f[i][j]=f[i-1][j];
			if (j-c[i]<0||j-c[i]>=SH*2) continue;
			if (f[i-1][j-c[i]]==-1) continue;
			if (f[i][j]==-1||f[i-1][j-c[i]]+a[i]>f[i][j])
				f[i][j]=f[i-1][j-c[i]]+a[i];
		}
	if (!f[n][SH]) --f[n][SH];
	printf("%d\n", f[n][SH]);

	return 0;
}
