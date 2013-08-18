#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

const int N = 102;

int a[N][N], sum[N][N];

int main() {
	int n; scanf("%d", &n);
	for (int i=1; i<=n; ++i)
		for (int j=1; j<=n; ++j) {
			scanf("%d", &a[i][j]);
			sum[i][j] = sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+a[i][j];
		}
	int ans = -0x7fffffff;
	for (int x1=1; x1<n; ++x1)
		for (int y1=1; y1<n; ++y1)
			for (int x2=x1+1; x2<=n; ++x2)
				for (int y2=y1+1; y2<=n; ++y2) {
					int tsum = sum[x2][y2]-sum[x1-1][y2]
							-sum[x2][y1-1]+sum[x1-1][y1-1];
					if (tsum>ans) ans = tsum;
				}
	printf("%d\n", ans);
	return 0;
}
