#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int N = 1003;

struct Poi {
	int x, y;
} p[N];

bool cmp(Poi a, Poi b) {
	if (a.x==b.x) return a.y<b.y;
	else return a.x<b.x;
}
/*
x1=1 y1=1 x2=2 y2=3
x3=4 y3=2 y4=
*/

int n;

bool b_find(int k, int x, int y) {
	int l=k, r=n, mid;
	while (l<r-1) {
		if (p[mid=(l+r)/2].x<=x) l = mid;
		else r = mid;
	}
	for (int i=l; i>=k&&p[i].x==x; --i)
		if (p[i].y==y) return 1;
	for (int i=l+1; i<n&&p[i].x==x; ++i)
		if (p[i].y==y) return 1;
	return 0;
}

int main() {
	while (scanf("%d", &n), n) {
		for (int i=0; i<n; ++i) scanf("%d%d", &p[i].x, &p[i].y);
		sort(p, p+n, cmp);
		//for (int i=0; i<n; ++i)
		int cnt = 0;
		for (int i=0; i<n-1; ++i)
			for (int j=i+1; j<n; ++j) {
				int x1 = p[i].x, x2 = p[j].x,
					y1 = p[i].y, y2 = p[j].y;
				if (y2<=y1) continue;
				int x3 = x2+y2-y1, y3 = y2-x2+x1,
					x4 = x1+y2-y1, y4 = y1-x2+x1;
				if (b_find(j+1, x3, y3)&&b_find(i+1, x4, y4)) ++cnt;
			}
		printf("%d\n", cnt);
	}
	//system("pause");
	return 0;
}