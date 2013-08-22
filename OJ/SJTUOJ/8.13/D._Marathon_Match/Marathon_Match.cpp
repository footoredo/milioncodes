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

const int N = 102, M=8005;

int tp[N], rt[N], v[N];
double p[N], ans[N], sum[N][M], f[N][M];
ll c[102][102];

void calcc(int n) {
	c[0][0]=1;
	for (int i=1; i<=n; ++i) {
		c[i][0]=1;
		for (int j=1; j<=i; ++j) c[i][j]=c[i-1][j]+c[i-1][j-1];
	}
}

int main() {
	int n, m, L; scanf("%d%d%d", &n, &m, &L);
	calcc(m); bool tk;
	REP(i, n) {
		scanf("%d%d%d", &tp[i], &rt[i], &v[i]);
		p[i]=tp[i]/100.0;
		double pp;
		REP(j, m+1) {
			pp=c[m][j];
			REP(k, j) pp*=p[i];
			REP(k, m-j) pp*=(1-p[i]);
			f[i][j*rt[i]]+=pp;
		}
		for (int j=m*rt[i]; j>=0; --j)
			sum[i][j]=sum[i][j+1]+f[i][j];
	}
	REP(i, n) {
		if (v[i]==0) { printf("0.0000000\n"); continue; }
		ans[i]=0;
		REP(j, m+1) {
			if (rt[i]==0&&j) break;
			double tans=f[i][j*rt[i]];
			REP(k, n) if (i!=k) {
				double t=L*1.0/v[i]+j*rt[i]-L*1.0/v[k];
				int tt; if (t<0) tt=0; else tt=(int)ceil(t);
				if (t+EPS>=tt) ++tt;
				if (tt>8000) tans*=0;
				else tans*=sum[k][tt];
			}
			ans[i]+=tans;
		}
		printf("%.7f\n", ans[i]);
	}
	return 0;
}
