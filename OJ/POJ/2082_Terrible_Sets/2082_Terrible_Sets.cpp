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

const int N = 50004;

typedef pair<int, int> Range;
#define lt first
#define rt second
inline bool in(int p, Range r) { return p>=r.lt&&p<=r.rt; }
inline bool in(Range r1, Range r2) { return r1.lt>=r2.lt&&r1.rt<=r2.rt; }
inline int mid(Range rg) { return MID(rg.lt, rg.rt); }
Range shift(Range rg, bool d) {
	return d?Range(mid(rg)+1, rg.rt):Range(rg.lt, mid(rg));
}
bool touch(Range r1, Range r2) {
	return in(r1.lt, r2)||in(r1.rt, r2)||in(r2, r1);
}

int cnt=1, root;
Range range[N*3];
int w[N], h[N], data[N*3], l[N*3], ch[N*3][2], sum[N];

void build(int &T, Range rg) {
	range[T=cnt++]=rg;
	ch[T][0]=ch[T][1]=0;
	if (rg.lt<rg.rt) REP(d, 2) build(ch[T][d], shift(rg, d));
}

void modify(int T, int p, int x) {
	if (range[T].lt==range[T].rt) { data[T]=x; l[T]=p; }
	else {
		REP(d, 2) if (in(p, shift(range[T], d))) modify(ch[T][d], p, x);
		bool d=data[ch[T][0]]>data[ch[T][1]];
		data[T]=data[ch[T][d]];
		l[T]=l[ch[T][d]];
	}
}

typedef pair<int, int> Ans;

int query(int T, Range rg) {
	if (in(range[T], rg)) return l[T];
	int ret=-1;
	REP(d, 2) if (touch(rg, range[ch[T][d]])) {
		int tans=query(ch[T][d], rg);
		if (ret==-1||h[tans]<h[ret]) ret=tans;
	}
	return ret;
}

inline int lowbit(int x) { return x&(-x); }
inline int mgcd(int x, int y) { return y?mgcd(y, x%y):x; }
inline int mmax(int x, int y) { return x<y?y:x; }

int solve(int l, int r) {
	if (l>r) return -0x7fffffff;
	int mid=query(root, Range(l, r));
	int ws=sum[r]; if (l) ws-=sum[l-1];
	int tans=ws*h[mid], tu=solve(l, mid-1), td=solve(mid+1, r);
	return mmax(mmax(tans, tu),td);
}

int main() {
	int n;
	build(root, Range(0, N-1));
	while (scanf("%d", &n), n+1) {
		REP(i, n*3) data[i]=-0x7fffffff;
		REP(i, n) {
			scanf("%d%d", &w[i], &h[i]);
			modify(root, i, h[i]);
			sum[i]=w[i];
			if (i) sum[i]+=sum[i-1];
		}
		printf("%d\n", solve(0, n-1));
	}
	return 0;
}