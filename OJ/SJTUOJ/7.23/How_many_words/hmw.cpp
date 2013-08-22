#include <iostream>
#include <cstdio>

using namespace std;

const int MODN = 1000000007;
int f[1000000][52], g[1000000][52];

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		int n; scanf("%d", &n);
		for (int i=1; i<=n; ++i)
			for (int j=0; j<52; ++j)
				if (i==1) { f[i][j]=1; g[i][j]=1; }
				else {
					for (int k=max(0, j-25); k<=min(51, j+25); ++k)
						g[i][j]=(g[i][j]+g[i-1][k])%MODN;
					for (int k=max(0, j-26); k<=min(51, j+26); ++k)
						f[i][j]=(f[i][j]+f[i-1][k])%MODN;
					/*if (j<26) f[i][j]=(f[i][j]+g[i-1][26+j])%MODN;
					else f[i][j]=(f[i][j]+g[i-1][j-26])%MODN;*/
				}/*if (j<26) {
					f[i][j]=g[i][j]=0;
					for (int k=0; k<=26+j; ++k) {
						f[i][j]=(f[i][j]+f[i-1][k])%MODN;
						if (k<26+j)
							g[i][j]=(g[i][j]+g[i-1][k])%MODN;
					}
					f[i][j]=(f[i][j]+g[i-1][26+j])%MODN;
				}
				else {
					f[i][j]=g[i][j]=0;
					for (int k=j-26; k<52; ++k) {
						f[i][j]=(f[i][j]+f[i-1][k])%MODN;
						if (k>j-26)
							g[i][j]=(g[i][j]+g[i-1][k])%MODN;
					}
					f[i][j]=(f[i][j]+g[i-1][j-26])%MODN;
				}*/
		int ans=0;
		for (int i=0; i<52; ++i)
			ans=(ans+f[n][i]-g[n][i])%MODN;
		printf("%d\n", ans);
	}
	return 0;
}
