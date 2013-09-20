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

int w[12], cnt=0, m;
bool f[1003][21][12];
int g[1003][21][12];

void tr(int i, int j, int k) {
	if (!i) return;
	int p=i&1?1:-1; tr(i-1, j-w[k]*p, g[i][j][k]);
	printf("%d", w[k]); if (i!=m) printf(" "); else printf("\n");
}

int main() {
	w[cnt++]=0;
	REP(i,10) {
		char c=getchar();
		if (c=='1') w[cnt++]=i+1;
	}
	scanf("%d", &m);
	f[0][10][0]=1;
	REP(i,m) REP(j,21) REP(k,cnt)
		if (!(i&1)&&(j>10)||(i&1)&&(j<10)) {
			int p=i&1?-1:1;
			REP(l,cnt) if ((f[i][j-w[k]*p][l]&&k!=l)&&(j-w[k]*p>=0&&j-w[k]*p<=20))
				f[i+1][j][k]=1, g[i+1][j][k]=l;
		}
	REP(j,21) REP(k,cnt) if (f[m][j][k]) {
		printf("YES\n"); tr(m,j,k); return 0;
	}
	printf("NO\n");
	return 0;
}
