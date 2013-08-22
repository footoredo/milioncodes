#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <string>

using namespace std;

typedef long long ll;

struct Win {
	int r, c, w, h;
} wis[102];

int n, m, ca=0;

inline bool inwin(int x, int y, Win p) {
	if ((x>=p.r&&y>=p.c)&&(x<p.r+p.h&&y<p.c+p.w)) return 1;
	else return 0;
}

int main() {
	while (scanf("%d",&n), n) {
		++ca; printf("Desktop %d:\n", ca);
		for (int i=1; i<=n; ++i)
			scanf("%d%d%d%d", &(wis[i].r), &(wis[i].c), &(wis[i].w), &(wis[i].h));
		scanf("%d", &m);
		while (m--) {
			int x, y, wn=0;
			scanf("%d%d", &x, &y);
			for (int i=n; i>=1; --i)
				if (inwin(x, y, wis[i])) {
					wn = i;
					break;
				}
			if (wn) printf("window %d\n", wn);
			else printf("background\n");
		}
	}
	return 0;
}
