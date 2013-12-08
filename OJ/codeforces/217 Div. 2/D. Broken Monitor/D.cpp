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
const string pr=".w+";
int n, m, a[N][N];
int sum[2][N][N], ts[N][N], tot=0;

int main() {
	scanf("%d%d", &n, &m);
	REP(i,n) {
	  getchar();
	  REP(j,m) {
		char ch=getchar();
		if (ch=='w') a[i+1][j+1]=1;
		sum[0][i+1][j+1]=sum[0][i+1][j]+a[i+1][j+1];
		sum[1][i+1][j+1]=sum[1][i][j+1]+a[i+1][j+1];
		tot+=a[i+1][j+1];
		ts[i+1][j+1]=ts[i][j+1]+ts[i+1][j]+a[i+1][j+1]-ts[i][j];
	}
	}
	int u, d, l, r;
	for (u=1; u<n && !sum[0][u][m]; ++u);
	for (d=n; d>u && !sum[0][d][m]; --d);
	for (l=1; l<m && !sum[1][n][l]; ++l);
	for (r=m; r>l && !sum[1][n][r]; --r);
	int inside=-(-ts[d-1][r-1]+ts[u][r-1]+ts[d-1][l]-ts[u][l]);
	if (r==l||d==u) inside=0;
	if (ts[d][r]-ts[u-1][r]-ts[d][l-1]+ts[u-1][l-1]-inside
		!=tot) {
		printf("-1\n"); return 0;
	}
	if (r-l!=d-u) {
		if (r-l<d-u) {
		  if (l==r) {
		    if (m-r>=d-u-r+l) {
		      r+=d-u-r+l;
		    }
		    else if (l-1>=d-u-r+l) {
		      l-=d-u-r+l;
		    }
		  }
			for (; l>1&&(l==r||!(sum[1][d-1][l]-sum[1][u][l]))&&r-l<d-u; --l);
			for (; r<m&&(l==r||!(sum[1][d-1][r]-sum[1][u][r]))&&r-l<d-u; ++r);
		}
		else {
		  if (d==u) {
		    if (n-d>=-(d-u-r+l)) {
		      d-=d-u-r+l;
		    }
		    else if (u-1>=-(d-u-r+l)) {
		      u+=d-u-r+l;
		    }
		  }
		  for (; u>1&&(u==d||!(sum[0][u][r-1]-sum[0][u][l]))&&r-l>d-u; --u);
			for (; d<n&&(u==d||!(sum[0][d][r-1]-sum[0][d][l]))&&r-l>d-u; ++d);
		}
	}
	if (r-l==d-u) {
		for (int i=l; i<=r; ++i) {
			if (!a[u][i]) a[u][i]=2;
			if (!a[d][i]) a[d][i]=2;
		}
		for (int i=u; i<=d; ++i) {
			if (!a[i][l]) a[i][l]=2;
			if (!a[i][r]) a[i][r]=2;
		}
		for (int i=1; i<=n; ++i) {
			for (int j=1; j<=m; ++j)
				printf("%c", pr[a[i][j]]);
			printf("\n");
		}
	}
	else printf("-1\n");
	return 0;
}
