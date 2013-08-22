#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <string>

using namespace std;

typedef long long ll;

const int N = 2003;
const int MODN = 1000000007;

ll f[N][N], sum[N][N], sumt[N][N], sumf[N], sumg[N][N], sumtg[N][N], g[N][N];

int main() {
	int n, m; scanf("%d%d", &n, &m);
	/*for (int i=0; i<=m; ++i)
		sum[0][i][0]=1;
	for (int i=1; i<=n; ++i) {
		f[i][0][0]=(i==1)?1:((f[i-1][0][0]+gs(i-1,m,1)+gs(i-1,m,0))%MODN);
		sum[i][0][0]=sum[i][1][0]=f[i][0][0];
		for (int j=2; j<=m; ++j) {
			f[i][j][0]=gs(i-1,j,0);
			f[i][j][1]=gs(i-1,j,0)+gs(i-1,)(sum[i-1][j][1])+sum[i-1][j][0]
		}
	}*/
	for (int i=2; i<=m; ++i) {
		f[i][1]=1;
		sumt[i][1] = i-1;
		sum[i][1] = sum[i-1][1]+(m-i+1);
		sumf[1]+=sum[i][1];
	}
	for (int j=2; j<=n; ++j) {
		for (int i=2; i<=m; ++i) {
			f[i][j]=((sum[i][j-1]-sumt[i][j-1]*(m-i))+MODN*(m-i))%MODN;
			sumt[i][j]=(sumt[i-1][j]+f[i][j])%MODN;
			sum[i][j]=(sum[i-1][j]+f[i][j]*(m-i+1))%MODN;
			g[i][j]=((sum[i-1][j-1]-sumt[i-1][j-1]*(m-i+1))+MODN*(m-i))%MODN;
			sumtg[i][j]=(sumtg[i-1][j]+g[i][j])%MODN;
			sumg[i][j]=(sumg[i-1][j]+g[i][j]*(m-i+1))%MODN;
		}
		/*for (int i=0; i<=m; ++i) {
			sum[i][j]=(sumt[i][j]*(m-i+1))%MODN;
			sumg[i][j]=(sumtg[i][j]*(m-i+1))%MODN;
		}*/
		sumf[j]=(sumf[j-1]+sumg[m][j])%MODN;
	}
	for (int j=2; j<=n; ++j)
		for (int i=)
	ll ans=0;
	for (int i=1; i<=n; ++i)
		for (int j=1; i+j-1<=n; ++j) {
			int l=i, r=i+j-1;
			ans=(ans+sumf[i]+sumf[n-r+1])%MODN;
		}
	cout<<ans<<endl;
	return 0;
}
