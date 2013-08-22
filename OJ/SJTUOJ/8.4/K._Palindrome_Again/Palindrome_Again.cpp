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
const int MODN = 1000000000, N = 1003;

#define REP(i, n) for (int i = 0; i < (int)(n); i++)
#define FOR(i, s, n) for (int i = (s); i < (int)(n); i++)
#define FOREQ(i, s, n) for (int i = (s); i <= (int)(n); i++)
#define FORIT(it, c) for (__typeof((c).begin())it = (c).begin(); it != (c).end(); it++)
#define MEMSET(v, h) memset((v), h, sizeof(v))
#define PB push_back
#define GU(a, b) if ((a)>(b)) (b)=(a);
#define SU(a, b) if ((a)<(b)) (b)=(a);

char st[N];
ll f[2][N][N], g[N][N], s[N][N];

int main() {
	f[0][0][0] = f[1][0][0] = 1; f[1][0][1] = 25;
	for (int i=1; i<=1000; ++i)
		for (int j=1; j<=1000; ++j) {
			f[0][i][j] = f[0][i-1][j-1]*2%MODN;
			if (j>1) f[0][i][j]=(f[0][i][j]+f[0][i-1][j-2]*24)%MODN;
			f[1][i][j] = f[1][i-1][j-1]*2%MODN;
			if (j>1) f[1][i][j]=(f[1][i][j]+f[1][i-1][j-2]*24)%MODN;
		}
	g[0][0] = 1;
	for (int j=0; j<=1000; ++j) s[0][j] = 1;
	for (int i=1; i<=1000; ++i) {
		s[i][0]=0;
		for (int j=0; j<=1000; ++j) {
			g[i][j] = g[i-1][j];
			if (j>1) g[i][j]=(g[i][j]+g[i-1][j-2]*25)%MODN;
			s[i][j] = g[i][j];
			if (j) s[i][j]=(s[i][j]+s[i][j-1])%MODN;
		}
	}
	int T, ca=1; scanf("%d", &T);
	while (T--) {
		printf("Case %d: ", ca++);
		int n, k, en=0; scanf("%d%d%s", &n, &k, st);
		bool d = n&1;
		for (int i=0; i<n/2; ++i) if (st[i]==st[n-i-1]) ++en;
		ll ans = 0;
		for (int i=0; i<=k; ++i)
			ans=(ans+f[d][n/2-en][i]*s[en][k-i])%MODN;
		cout<<ans<<endl;
	}
	return 0;
}
