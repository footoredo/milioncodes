#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

const int N = 5003;

int a[N], f[N], g[N];

int main() {
	int n; scanf("%d", &n); ++n;
	for (int i=1; i<n; ++i)
		scanf("%d", &a[i]);
	a[n] = -1;

	int ans=0;
	for (int i=1; i<=n; ++i) {
		f[i] = 1; 
		for (int j=1; j<i; ++j)
			if (a[j]>a[i]&&f[j]>=f[i])
				f[i] = f[j]+1;
		int last = -1;
		for (int j=i-1; j>=1; --j)
			if ((f[j]==f[i]-1&&a[j]>a[i])&&a[j]!=last) {
				g[i] += g[j];
				last = a[j]; 
			}
		if (f[i]>ans) ans = f[i];
		if (!g[i]) g[i] = 1;
	}

	printf("%d %d\n", f[n]-1, g[n]);

	system("pause");
	return 0;
}
