#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <string>

using namespace std;

const int N = 200005;

struct Data {
	int x, oo, no;
} a[N];

inline int lowbit(int x) {
	return x&(-x);
}

int prev[N], mhash[N];
int d[N], n;
bool g[N];

bool cmp1(Data a, Data b) {
	return a.x<b.x;
}

bool cmp2(Data a, Data b) {
	return a.oo<b.oo;
}

int getsum(int x) {
	int ret=0;
	for (; x; x-=lowbit(x)) ret+=d[x];
	return ret;
}

void add(int x, int de) {
	for (; x<=n; x+=lowbit(x)) d[x]+=de;
}

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i=1; i<=n; ++i) {
			scanf("%d", &a[i].x);
			a[i].oo = i;
		}
		sort(a+1, a+n+1, cmp1);
		int cnt=0;
		for (int i=1; i<=n; ++i) {
			if (i>1&&a[i].x!=a[i-1].x) ++cnt;
			a[i].no = cnt;
		}
		sort(a+1, a+n+1, cmp2);
		memset(mhash, 0, sizeof mhash);
		memset(d, 0, sizeof d);
		for (int i=1; i<=n; ++i) {
			prev[i] = mhash[a[i].no];
			mhash[a[i].no] = i;
		}
		bool ok=1;
		for (int i=1; i<=n; ++i)
			if (prev[i]) {
				int k = prev[i];
				if (g[k]) {
					g[k] = 0;
					add(k, -1);
				}
				if (k==i-1) {
					ok=0; break;
				}
				int l = prev[k];
				int t = getsum(i)-getsum(l);
				if (t<k-l-1) {
					ok=0; break;
				}
			}
			else {
				add(i, 1);
				g[i] = 1;
			}
		if (ok) printf("non-boring\n");
		else printf("boring\n");
	}
	return 0;
}
