#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 100005;

int p[N], indeg[N];
bool appear[N];

int mfind(int x) {
	if (x==p[x]) return x;
	else return p[x]=mfind(p[x]);
}

bool unionset(int x, int y) {
	int fx=mfind(x), fy=mfind(y);
	if (fx==fy) return 0;
	p[mfind(y)]=mfind(x);
	return 1;
}

int main() {
	int k=0;
	while (++k) {
		int x, y;
		bool istree = 1, over=0, empty=1;
		for (int i=1; i<N; ++i) p[i]=i;
		memset(indeg, 0, sizeof indeg);
		memset(appear, 0, sizeof appear);
		while (scanf("%d%d", &x, &y), x||y) {
			if (x==-1) {
				over = 1;
				break;
			}
			empty = 0;
			++indeg[y];
			appear[x]=appear[y]=1;
			if (!unionset(x, y)) istree=0;
		}
		if (over) break;
		int cnt=0;
		for (int i=1; i<N; ++i) {
			if (indeg[i]==0&&appear[i]) ++cnt;
			if (indeg[i]>1) { istree=0; break; }
		}
		if (cnt==1&&istree||empty)
			printf("Case %d is a tree.\n", k);
		else printf("Case %d is not a tree.\n", k);
	}

	return 0;
}
