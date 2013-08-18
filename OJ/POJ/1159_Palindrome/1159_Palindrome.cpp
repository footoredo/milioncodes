#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace std;

const int N = 5003;

short f[N][N];
char s[N];

int main() {
	int n; scanf("%d", &n);
	scanf("%s", s+1);
	for (int i=1; i<=n; ++i) f[i][1] = 0;
	for (int i=2; i<=n; ++i)
		for (int j=n; j>=1; --j) {
			f[j][i] = min(f[j+1][i-1], f[j][i-1])+1;
			if (s[j]==s[j+i-1]) f[j][i] = min(f[j][i], f[j+1][i-2]);
		}
	printf("%d\n", f[1][n]);
	return 0;
}
