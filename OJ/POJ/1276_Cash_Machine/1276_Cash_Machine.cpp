#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;

int da[10004], f[100005];

int main() {
	int cash;
	while (scanf("%d", &cash)!=EOF) {
		int m, n=0; scanf("%d", &m);
		while (m--) {
			int x, d; scanf("%d%d", &x, &d);
			int b=1;
			for (; b<x; b<<=1) {
				da[++n] = b*d;
				x-=b;
			}
			da[++n] = x*d;
		}
		memset(f, 0, sizeof f);
		int ans = 0; bool now=0;
		for (int i=1; i<=n; ++i)
			for (int j=cash; j>=0; --j)
				if (da[i]<=j) f[j]=max(f[j], f[j-da[i]]+da[i]);
		printf("%d\n", f[cash]);
	}
	return 0;
}
