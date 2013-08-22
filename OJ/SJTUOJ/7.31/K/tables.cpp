#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <iostream>
#include <math.h>
#include <assert.h>
#include <vector>
#include <queue>
#include <string>
#include <map>
#include <set>

using namespace std;
typedef long long ll;
typedef unsigned int uint;
typedef unsigned long long ull;
static const double EPS = 1e-9;
static const double PI = acos(-1.0);

#define REP(i, n) for (int i = 0; i < (int)(n); i++)
#define FOR(i, s, n) for (int i = (s); i < (int)(n); i++)
#define FOREQ(i, s, n) for (int i = (s); i <= (int)(n); i++)
#define FORIT(it, c) for (__typeof((c).begin())it = (c).begin(); it != (c).end(); it++)
#define MEMSET(v, h) memset((v), h, sizeof(v))
#define PB push_back
#define GU(a, b) if ((a)>(b)) (b)=(a);
#define SU(a, b) if ((a)<(b)) (b)=(a);

const int N = 1003;

int na, nb, ma, mb, size;
vector<int> nums;
int a[N][N], b[N][N], d[N*N*3];

inline int lowbit(int x) {
	return x&(-x);
}

int query(int x) {
	int ret=0;
	for (; x; ret+=d[x], x-=lowbit(x));
	return ret;
}

void modify(int x, int delta) {
	for (; x<=size; d[x]+=delta, x+=lowbit(x));
}

int main() {
	scanf("%d%d", &na, &ma);
	REP(i, na) REP(j, ma) {
		scanf("%d", &a[i][j]);
		nums.push_back(a[i][j]);
	}
	scanf("%d%d", &nb, &mb);
	REP(i, nb) REP(j, mb) {
		scanf("%d", &b[i][j]);
		nums.push_back(b[i][j]);
	}
	size = nums.size()+1;
	sort(nums.begin(), nums.end());
	REP(i, na) REP(j, ma) a[i][j] = lower_bound(nums.begin(), nums.end(), a[i][j])-nums.begin()+1;
	REP(i, nb) REP(j, mb) b[i][j] = lower_bound(nums.begin(), nums.end(), b[i][j])-nums.begin()+1;
	int x=0, y=0;
	ll ans=0;
	REP(i, na-nb+1) REP(j, ma-mb+1) modify(a[i][j], 1);
	bool d=1;
	while (1) {
		ans+=query(b[x][y]-1);
		if ((y==mb-1&&d)||(y==0&&!d)) {
			if (x+1==nb) break;
			REP(j, ma-mb+1) {
				modify(a[x][y+j], -1);
				modify(a[x+na-nb+1][y+j], 1);
			}
			++x;
			d=!d;
		}
		else if (d) {
			REP(i, na-nb+1) {
				modify(a[x+i][y], -1);
				modify(a[x+i][y+ma-mb+1], 1);
			}
			++y;
		}
		else {
			REP(i, na-nb+1) {
				modify(a[x+i][y+ma-mb], -1);
				modify(a[x+i][y-1], 1);
			}
			--y;
		}
	}
	cout<<ans<<endl;
	return 0;
}
/*
5 4
1 7 4 0
8 8 2 4
1 7 1 1
7 6 1 4
2 2 1 6
3 2
7 6
1 8
9 2
*/
