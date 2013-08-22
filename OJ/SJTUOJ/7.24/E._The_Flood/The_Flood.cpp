#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <string>

using namespace std;

typedef long long ll;

const int N = 152;
const int dx[4] = {1, -1, 0, 0};
const int dy[4] = {0, 0, 1, -1};

int n, m, h[N][N], ca=0;
bool oed[N][N], vis[N][N];

inline bool cansp(int x, int y, int r) {
	if (r<h[x][y]) return 0;
	for (int i=0; i<4; ++i)
		if (oed[x+dx[i]][y+dy[i]]) return 1;
	return 0;
}

void sp(int x, int y, int r) {
	oed[x][y] = 1;
	for (int i=0; i<4; ++i) {
		int a = x+dx[i], b = y+dy[i];
		if (!oed[a][b]&&h[a][b]<=r) sp(a, b, r);
	}
}

void travel(int x, int y) {
	vis[x][y] = 1;
	for (int i=0; i<4; ++i) {
		int a = x+dx[i], b = y+dy[i];
		if (!oed[a][b]&&!vis[a][b]) travel(a, b);
	}
}

int main() {
	while (scanf("%d%d", &n, &m), n) {
		++ca;
		memset(oed, 0, sizeof oed);
		memset(h, 0, sizeof h);
		int hightest=0;
		for (int i=1; i<=n; ++i)
			for (int j=1; j<=m; ++j) {
				scanf("%d", &h[i][j]);
				if (h[i][j]>hightest)
					hightest = h[i][j];
			}
		for (int i=0; i<=n+1; ++i)
			oed[i][0] = oed[i][m+1] = 1;
		for (int i=0; i<=m+1; ++i)
			oed[0][i] = oed[n+1][i] = 1;
		bool two = 0;
		for (int r=0; r<=hightest; ++r) {
			for (int i=1; i<=n; ++i)
				for (int j=1; j<=n; ++j)
					if (!oed[i][j]&&cansp(i, j, r))
						sp(i, j, r);
			memset(vis, 0, sizeof vis);
			bool mark = 0;
			for (int i=1; i<=n&&!two; ++i)
				for (int j=1; j<=n; ++j)
					if (!oed[i][j]&&!vis[i][j]) {
						if (mark) {
							two = 1;
							break;
						}
						travel(i, j);
						mark = 1;
					}
			if (two) {
				printf("Case %d: Island splits when ocean rises %d feet.\n", ca, r);
				break;
			}
		}
		if (!two)
			printf("Case %d: Island never splits.\n", ca);
	}
	return 0;
}
