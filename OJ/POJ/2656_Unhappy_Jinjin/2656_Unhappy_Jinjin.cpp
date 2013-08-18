#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;

int main() {
	int n;
	while (scanf("%d", &n), n) {
		int ans=0, ansh=8;
		for (int i=1; i<=n; ++i) {
			int x, y; scanf("%d%d", &x, &y);
			if (x+y>ansh) {
				ansh = x+y;
				ans = i;
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}