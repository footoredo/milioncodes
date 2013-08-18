#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

inline int lowbit(int x) {
	return x&(-x);
}

const int N = 100005;

int n;
long long d[N], d_help[N], origin[N];

void update(long long *d, int p, long long delta) {
	for (; p<=n; d[p]+=delta, p+=lowbit(p)) ;
}

long long query(long long *d, int p) {
	long long ret;
	for (ret=0; p; ret+=d[p], p-=lowbit(p)) ;
	return ret;
}

void add(int a, int b, long long c) {
	update(d, a, c);
	update(d, b+1, -c);
	update(d_help, a, c*a);
	update(d_help, b+1, -c*(b+1));
}

long long sum(int a) {
	if (!a) return 0;
	return (long long)(a+1)*query(d, a) - query(d_help, a);
}

int main() {
	int q;
	scanf("%d%d", &n, &q); ++n;
	for (int i=1; i<n; ++i) {
		scanf("%I64d", &origin[i]);
		add(i, i, origin[i]);
	}
	while (q--) {
		char s[5]; scanf("%s", s);
		int a, b; long long c;
		switch (s[0]) {
			case 'Q':
				scanf("%d%d", &a, &b);
				printf("%I64d\n", sum(b)-sum(a-1));
				break;
			case 'C':
				scanf("%d%d%I64d", &a, &b, &c);
				add(a, b, c);
				break;
		}
	}
	return 0;
}