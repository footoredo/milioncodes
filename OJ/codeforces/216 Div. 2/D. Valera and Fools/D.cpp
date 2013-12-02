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
#define MID(l, r) (((l)+(r))>>1)

typedef pair<int, int> Range;
#define lt first
#define rt second
inline bool in(int p, Range r) { return p>=r.lt&&p<=r.rt; }
inline bool in(Range r1, Range r2) { return r1.lt>=r2.lt&&r1.rt<=r2.rt; }
inline int mid(Range rg) { return MID(rg.lt, rg.rt); }
Range shift(bool d, Range rg) {
	return d?Range(mid(rg)+1, rg.rt):Range(rg.lt, mid(rg));
}

inline int lowbit(int x) { return x&(-x); }
inline int mgcd(int x, int y) { return y?mgcd(y, x%y):x; }

typedef pair<int, int> op;
typedef pair<op, int> Stat;

const int N = 3103;
int n, k, p[N];
int sum[N], tot[N], ans=0;
bool f[N][N];

queue<Stat> Q;
void BFS() {
	Q.push(make_pair(make_pair(1,2),0));
	f[1][2]=1;
	while (!Q.empty()) {
		++ans; Stat ts=Q.front(); op to=ts.first; Q.pop();
		if (to.second>n) continue;
		if (ts.second>=k) continue;
		if (sum[n]-sum[to.second-1]) {
			if (p[to.first]) if (!f[to.second+1][to.second+2]) {
				Q.push(make_pair(make_pair(to.second+1,to.second+2),ts.second+1));
				f[to.second+1][to.second+2]=1;
			}
			if (p[to.first]!=100) if (!f[to.second][to.second+1]) {
				Q.push(make_pair(make_pair(to.second,to.second+1),ts.second+1));
				f[to.second][to.second+1]=1;
			}
		}
		if (tot[n]-tot[to.second-1]) continue;
		if (p[to.first]) if (!f[to.first][to.second+1]) {
			Q.push(make_pair(make_pair(to.first,to.second+1),ts.second+1));
			f[to.first][to.second+1]=1;
		}
	}
}

int main() {
	scanf("%d%d", &n, &k);
	if (n==1) {
		printf("1\n");
		return 0;
	}
	REP(i,n) {
		scanf("%d", &p[i+1]);
		sum[i+1]=sum[i]+p[i+1];
		tot[i+1]=tot[i]+(p[i+1]==100);
	}
	BFS();
	printf("%d\n", ans);
	return 0;
}
