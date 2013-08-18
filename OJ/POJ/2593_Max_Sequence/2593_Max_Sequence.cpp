#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

const int N = 100005;

int f[2][N], a[N];

int main() {
	int n;
	while (scanf("%d", &n),n) {
		f[0][0] = f[1][n+1] = 0;
		for (int i=1; i<=n; ++i) {
			scanf("%d", &a[i]);
			f[0][i] = f[0][i-1] + a[i];
		}
		for (int i=n; i>=1; --i)
			f[1][i] = f[1][i+1] + a[i];
		int minf=0;
		for (int i=1; i<=n; ++i) {
			int tans = (i==1)?f[0][i]:f[0][i-1];
			if (f[0][i]-minf>tans) tans = f[0][i]-minf;
			if (f[0][i]<minf) minf = f[0][i];
			f[0][i] = tans;
		}
		minf = 0;
		for (int i=n; i>=1; --i) {
			int tans = (i==n)?f[1][i]:f[1][i+1];
			if (f[1][i]-minf>tans) tans = f[1][i]-minf;
			if (f[1][i]<minf) minf = f[1][i];
			f[1][i] = tans;
		}
		int ans = -0x7fffffff;
		for (int i=1; i<n; ++i)
			if (f[0][i]+f[1][i+1]>ans)
				ans = f[0][i]+f[1][i+1];
		printf("%d\n", ans);
	}
	return 0;
}

