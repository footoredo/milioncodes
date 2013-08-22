#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <string>

using namespace std;

typedef long long ll;

const int rad[10]={20, 40, 60, 80, 100, 120, 140, 160, 180, 200};

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		int n; scanf("%d", &n);
		int p=0;
		while (n--) {
			int x, y; scanf("%d%d", &x, &y);
			int dis = x*x+y*y, tp=0;
			for (int i=0; !tp&&i<10; ++i)
				if (dis<=rad[i]*rad[i])
					tp = 11-rad[i]/20;
			p+=tp;
		}
		printf("%d\n", p);
	}
	return 0;
}
