#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <string>

using namespace std;

typedef long long ll;

const int N = 51;

int n, fin[N], d[N][N], anslist[N], cnt, tf[N];
bool crashed[N];

void crash(int dep, int x) {
	crashed[x] = 1;
	//printf("crashing %d.\n", x);
	for (int i=1; i<=n; ++i)
		tf[i]-=d[x][i];
	bool rem=0;
	for (int i=1; i<=n; ++i)
		if (tf[i]<0&&!crashed[i]) {
			rem = 1;
			crash(dep+1, i);
		}
	if (!rem&&dep==n-1)
		for (int i=1; i<=n; ++i)
			if (!crashed[i])
				anslist[cnt++] = i;
	crashed[x] = 0;
	for (int i=1; i<=n; ++i)
		tf[i]+=d[x][i];
}

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i=1; i<=n; ++i)
			for (int j=1; j<=n; ++j) {
				scanf("%d", &d[i][j]);
				fin[i]-=d[i][j];
			}
		cnt=0;
		for (int i=1; i<=n; ++i) {
			if (fin[i]<0) {
				memset(crashed, 0, sizeof crashed);
				memcpy(tf, fin, sizeof fin);
				crash(1, i);
			}
		}
		sort(anslist, anslist+cnt);
		if (!cnt) printf("0\n");
		else {
			printf("%d", anslist[0]);
			for (int i=1; i<cnt; ++i) printf(" %d", anslist[i]);
			printf("\n");
		}
	}
	return 0;
}
