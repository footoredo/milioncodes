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

const int N = 1003, VAL=185;

int n, m, f[N][N], ans[N][N];
char tmp[N];
bool c[N][N];

int main() {
	scanf("%d%d", &n, &m);
	srand(213213);
	REP(i, n) {
		scanf("%s", tmp);
		REP(j, m)
			c[i][j]=tmp[j]-'0';
	}
	REP(i, n) {
		int t=-1;
		REP(j, m) {
			if (c[i][j]) t=j;
			if (t==-1) f[i][j]=-1;
			else f[i][j]=(j-t)*(j-t);
		}
		t=-1; int tans;
		for (int j=m-1; j>=0; --j) {
			if (c[i][j]) t=j;
			if (t==-1) tans=-1;
			else tans=(j-t)*(j-t);
			if (f[i][j]==-1||(tans!=-1&&tans<f[i][j]))
				f[i][j] = tans;
			ans[i][j]=f[i][j];
		}
	}
	REP(i, n) REP(j, m) {
		int u=min(n, VAL), d=max(0,n-VAL);
		for (int k=0; k<u; ++k) if (f[k][j]>-1) {
			int tans = (i-k)*(i-k)+f[k][j];
			if (ans[i][j]==-1||tans<ans[i][j])
				ans[i][j] = tans;
		}
		for (int k=d; k<n; ++k) if (f[k][j]>-1) {
			int tans = (i-k)*(i-k)+f[k][j];
			if (ans[i][j]==-1||tans<ans[i][j])
				ans[i][j] = tans;
		}

	}
	REP(i, n) {
		REP(j, m-1) printf("%d ", ans[i][j]);
		printf("%d\n", ans[i][m-1]);
	}
	return 0;
}
