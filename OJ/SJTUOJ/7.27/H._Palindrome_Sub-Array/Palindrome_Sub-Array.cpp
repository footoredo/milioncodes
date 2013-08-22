#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <string>

using namespace std;

typedef long long ll;

const int N = 302;

int n, m;
int stf[2][N][N][10], stg[2][N][N][10];
int f[2][N][N], g[2][N][N], a[N][N];

int getminf(bool b, int i, int j, int len) {
	int k;
	for (k=0; (1<<k)<=len; ++k); --k;
	return min(stf[b][i][j][k], stf[b][i+len-(1<<k)][j][k]);
}

int getming(bool b, int i, int j, int len) {
	int k;
	if (i<0||j<0) return -1;
	for (k=0; (1<<k)<=len; ++k); --k;
	return min(stg[b][i][j][k], stg[b][i][j+len-(1<<k)][k]);
}

bool check(bool b, int size) {
	for (int i=0; i<n; ++i)
		for (int j=0; j<m; ++j)
			if (getminf(b,i,j,size)>=size&&getming(b,(i*2+size-1)>>1,j-(size>>1)+!b,size)>=size)
				return 1;
	return 0;
}

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &m);
		for (int i=0; i<n; ++i)
			for (int j=0; j<m; ++j)
				scanf("%d", &a[i][j]);
		memset(f, 0, sizeof f);
		memset(g, 0, sizeof g);
		memset(stf, 0, sizeof stf);
		memset(stg, 0, sizeof stg);
		for (int i=0; i<n; ++i)
			for (int j=0; j<m; ++j) {
				f[1][i][j]=g[1][i][j]=1;
				//if (a[i][j]==a[i][j+1]) f[0][i][j]=2;
				//if (a[i][j]==a[i+1][j]) g[0][i][j]=2;
				for (int k=1; j-k>=0&&j+k<m; ++k)
					if (a[i][j-k]==a[i][j+k])
						f[1][i][j]=(k<<1)+1;
					else break;
				for (int k=1; i-k>=0&&i+k<n; ++k)
					if (a[i-k][j]==a[i+k][j])
						g[1][i][j]=(k<<1)+1;
					else break;
				for (int k=1; j-k+1>=0&&j+k<m; ++k)
					if (a[i][j-k+1]==a[i][j+k])
						f[0][i][j]=k<<1;
					else break;
				for (int k=1; i-k+1>=0&&i+k<n; ++k)
					if (a[i-k+1][j]==a[i+k][j])
						g[0][i][j]=k<<1;
					else break;
			}
		for (int i=0; i<n; ++i)
			for (int j=0; j<m; ++j) {
				stf[0][i][j][0]=f[0][i][j];
				stf[1][i][j][0]=f[1][i][j];
				stg[0][i][j][0]=g[0][i][j];
				stg[1][i][j][0]=g[1][i][j];
			}
		for (int j=0; j<m; ++j)
			for (int i=n-1; i>=0; --i)
				for (int k=1; i+(1<<k)-1<n; ++k) {
					stf[0][i][j][k]=min(stf[0][i][j][k-1],stf[0][i+(1<<k-1)][j][k-1]);
					stf[1][i][j][k]=min(stf[1][i][j][k-1],stf[1][i+(1<<k-1)][j][k-1]);
				}
		for (int i=0; i<n; ++i)
			for (int j=m-1; j>=0; --j)
				for (int k=1; j+(1<<k)-1<m; ++k) {
					stg[0][i][j][k]=min(stg[0][i][j][k-1],stg[0][i][j+(1<<k-1)][k-1]);
					stg[1][i][j][k]=min(stg[1][i][j][k-1],stg[1][i][j+(1<<k-1)][k-1]);
				}
		int l=0, r=min(n,m)/2+1, ans=0;
		while (l<r-1) {
			int mid = (l+r)/2;
			if (check(0,mid*2)) l=mid;
			else r=mid;
		}
		ans=l*2;
		l=0; r=min(n,m)/2+1;
		while (l<r-1) {
			int mid = (l+r)/2;
			if (check(1,mid*2+1)) l=mid;
			else r=mid;
		}
		ans=max(ans,l*2+1);
		printf("%d\n", ans);
	}
	return 0;
}
