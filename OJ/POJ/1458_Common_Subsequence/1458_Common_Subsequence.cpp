#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;

const int N = 502;

int f[N][N];
char a[N], b[N];

int main() {
	while (scanf("%s%s", a+1, b+1)!=EOF) {
		int n = strlen(a+1), m=strlen(b+1);

		int ans=0;
		f[0][1]=f[1][0]=f[0][0]=0;
		for (int i=1; i<=n; ++i)
			for (int j=1; j<=m; ++j) {
				f[i][j] = max(f[i-1][j], f[i][j-1]);
				if (a[i]==b[j]) f[i][j] = max(f[i][j], f[i-1][j-1]+1);
				if (f[i][j]>ans) ans = f[i][j];
			}

		printf("%d\n", ans);
	}

	system("pause");
	return 0;
}
