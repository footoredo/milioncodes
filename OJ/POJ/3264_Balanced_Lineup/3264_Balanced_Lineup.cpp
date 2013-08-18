#include <iostream>
#include <cstdlib>
#include <cstdio>

using namespace std;

const int N = 50004;

inline int mmax(int a, int b) { return a>b?a:b; }
inline int mmin(int a, int b) { return a<b?a:b; }

int n, origin[N], d_max[N], d_min[N];

inline int lowbit(int x) {
	return x&(-x);
}

void update(int *d, int x, int val, int (*cmp)(int, int)) {
	for (int t=origin[x]; x<=n; d[x]=cmp(d[x], t), x+=lowbit(x));
}

int query(int *d, int l, int r, int (*cmp)(int, int)) {
	int ret;
	for (ret=origin[r]; r>=l; )
		if (r-lowbit(r)<l-1) ret = cmp(ret, origin[r--]);
		else { ret = cmp(ret, d[r]); r-=lowbit(r); }
	return ret;
}

int main() {
	int q; scanf("%d%d", &n, &q);
	for (int i=1; i<=n; ++i) d_min[i] = 0x7fffffff;
	for (int i=1; i<=n; ++i) {
		int x; scanf("%d", &x);
		origin[i] = x;
		update(d_min, i, x, mmin);
		update(d_max, i, x, mmax);
	}
	//for (int i=1; i<=n; ++i) printf("%d ", d_min[i]); printf("\n");
	//for (int i=1; i<=n; ++i) printf("%d ", d_max[i]); printf("\n");
	while (q--) {
		int l, r; scanf("%d%d", &l, &r);
		printf("%d\n", query(d_max,l,r,mmax) - query(d_min,l,r,mmin));
	}
	return 0;
}