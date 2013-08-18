#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int N = 1003;

typedef long long ll;

ll g[N][N], sum[N][N];
int req[100005], reqn, n;

int main() {
	int maxn = 0;
	while (scanf("%d", &n), n) {
		req[reqn++] = n;
		if (n>maxn) maxn = n;
	}
	maxn = (maxn+1)/2;
	for (int i=0; i<=maxn*2+1; ++i) sum[0][i] = 1;
	for (int i=1; i<=maxn; ++i) {
		sum[i][0] = 0;
		for (int j=1; j<=i; ++j) {
			g[i][j] += sum[i-j][min(i-j, j)];
			sum[i][j] = sum[i][j-1]+g[i][j];
		}
	}
	//printf("%d\n", sum[3][3]);
	for (int i=0; i<reqn; ++i) {
		int n = req[i];
		ll ans=(n&1)?0:sum[n/2][n/2];
		for (int j=1; j<=n; ++j)
			if (!((n-j)&1)) {
				ans += sum[(n-j)/2][min((n-j)/2, j)];
				//if (n==6) printf("%d %d\n", j, sum[(n-j)/2][min((n-j)/2, j)]);
			}
		cout<<n<<" "<<ans<<endl;
	}
	return 0;
}
