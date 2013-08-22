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

inline int lowbit(int x) { return x&(-x); }
inline int mgcd(int x, int y) { return y?mgcd(y, x%y):x; }

const int N = 12, X=10004;

typedef pair<int, int> Range;
#define ll first
#define rr second

struct node {
	Range r;
	int t;
	node(Range r, int t): r(r), t(t) {}
};

int f[X], r[N], ans;
map<Range, bool> hash;
queue<node> Q;

void BFS() {
	while (!Q.empty()) {
		node tn=Q.front(); Q.pop();
		int xl=tn.r.ll, xu=tn.r.rr, t=tn.t;
		if (t==7) return;
		int xr=xu; xu=xr*2-xl;
		if (xl<xu&&xl<=xr&&xr<=xu&&xu>=0&&xu<=10000&&f[xl]*f[xr]<0&&!hash[Range(xl,xu)]) {
			Q.push(node(Range(xl,xu),t+1));
			if (f[xl]*f[xu]<0) ++ans;
			hash[Range(xl,xu)]=1;
		}
		xu=xr; xr=xl; xl=xr*2-xu;
		if (xl<xu&&xl<=xr&&xr<=xu&&xl>=0&&xl<=10000&&f[xl]*f[xr]>0&&!hash[Range(xl,xu)]) {
			Q.push(node(Range(xl,xu),t+1));
			if (f[xl]*f[xu]<0) ++ans;
			hash[Range(xl,xu)]=1;
		}
	}
}

char rubbish[5];

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		int tr=-1, xr, n=0;
		getchar();
		while (scanf("(x-%d)", &tr), tr+1) {
			r[n++]=tr;
			//printf("%d\n", tr);
			tr=-1;
		}
		hash.clear();
		gets(rubbish);
		REP(i, 10001) {
			f[i]=1;
			REP(j, n)
				if (i<r[j]) f[i]*=-1;
				else if (i>r[j]) f[i]*=1;
				else f[i]*=0;
		}
		scanf("%d", &xr); xr*=2;
		ans=0; while (!Q.empty()) Q.pop();
		for (int xl=0; xr-2*xl>0; ++xl)
			if (xr-xl<=10000) {
				int xu=xr-xl;
				if (f[xl]&&f[xu]) {
					Q.push(node(Range(xl, xu),1));
					hash[Range(xl, xu)]=1;
					if (f[xl]*f[xu]<0) ++ans;
				}
			}
		BFS();
		printf("%d\n", ans);
	}
	return 0;
}

/*
2
(x-8469)(x-6335)=0
8469
(x-2384)(x-7423)(x-8718)=0
8718
*/
