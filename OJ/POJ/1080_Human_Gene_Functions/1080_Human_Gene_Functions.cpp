#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

inline int ton(char c) {
	switch (c) {
		case 'A': return 1;
		case 'C': return 2;
		case 'G': return 3;
		case 'T': return 4;
	}
}

int f[102][102], a[102], b[102], map[5][5];
char sa[102], sb[102];

int main() {
	map[1][1]=5; map[1][2]=map[2][1]=-1; map[1][3]=map[3][1]=-2;
	map[2][2]=5; map[1][4]=map[4][1]=-1; map[1][0]=map[0][1]=-3;
	map[3][3]=5; map[2][3]=map[3][2]=-3; map[2][4]=map[4][2]=-2;
	map[4][4]=5; map[0][2]=map[2][0]=-4; map[0][3]=map[3][0]=-2;
	map[1][1]=5; map[3][4]=map[4][3]=-2; map[4][0]=map[0][4]=-1;
	int T; scanf("%d", &T);
	while (T--) {
		int n, m;
		scanf("%d%s%d%s", &n, sa, &m, sb);
		for (int i=0; i<n; ++i) a[i]=ton(sa[i]);
		for (int i=0; i<m; ++i) b[i]=ton(sb[i]);
		memset(f, -100, sizeof f);
		f[n][m]=0;
		for (int i=n-1; i>=0; --i)
			for (int j=m-1; j>=0; --j) {
				//if (i==n&&j==m) continue;
				f[i][j]=map[a[i]][b[j]]+f[i+1][j+1];
				if (j<m-1) f[i][j]=max(f[i][j], f[i][j+1]+map[0][b[j]]);
				if (i<n-1) f[i][j]=max(f[i][j], f[i+1][j]+map[a[i]][0]);
			}
		printf("%d\n", f[0][0]);
	}
	return 0;
}
