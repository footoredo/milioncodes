#include <iostream>
#include <cstdio>

using namespace std;

const int N = 102;

const int dx[4] = {0, 1, 0,-1};
const int dy[4] = {1, 0,-1, 0};

int n, m;
int h[N][N], f[N][N];

int solve_f(int x, int y) {
	int t;
	if (f[x][y]) return f[x][y];
	f[x][y] = 1;
	for (int i=0; i<4; ++i) {
		int nx = x+dx[i], ny=y+dy[i];
		if (nx<0||ny<0||nx==n||ny==m) continue;
		if (h[nx][ny]>h[x][y])
			if ((t=solve_f(nx, ny)+1)>f[x][y])
				f[x][y] = t;
	}
	return f[x][y];
}

int solve() {
	int ret=0, t;
	memset(f, 0, sizeof f);
	for (int i=0; i<n; ++i)
		for (int j=0; j<m; ++j)
			if ((t=solve_f(i, j))>ret)
				ret = t;
	return ret;
}

int main() {
	scanf("%d%d", &n, &m);
	for (int i=0; i<n; ++i)
		for (int j=0; j<m; ++j)
			scanf("%d", &h[i][j]);
	printf("%d\n", solve());
	//system("pause");
	return 0;
}