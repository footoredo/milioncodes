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
static const double EPS = 1e-7;
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
inline double mabs(double x) { return x<0?-x:x; }

const int N = 51, X = 302;

int n, v, x, y;
int L[N], B[N], R[N], T[N];
int d[X][X], hd[X][X];

void add(int *d, int p, int x) {
	for (; p<X; d[p]+=x, p+=lowbit(p));
}

int _query(int *d, int p) {
	int ret=0;
	for (; p; ret+=d[p], p-=lowbit(p));
	return ret;
}

int query(int x, int l, int r) {
	return (_query(d[x], r)*(r+1)-_query(hd[x], r)) -
		(_query(d[x], l-1)*l-_query(hd[x], l-1));
}

int main() {
	scanf("%d%d%d%d", &n, &v, &x, &y); ++x; ++y;
	REP(i, n) {
		scanf("%d%d%d%d", &L[i], &B[i], &R[i], &T[i]);
		++L[i]; ++B[i]; ++R[i]; ++T[i];
		FOREQ(j, L[i], R[i]) {
			add(d[j], B[i], 1); add(d[j], T[i], -1);
			add(hd[j], B[i], B[i]); add(hd[j], T[i], -T[i]);
		}
	}
	if (!x&&!y) { printf("Yes\n"); return 0; }
	if (!v) { printf("No\n"); return 0; }
	for (double z=EPS; z<0.5*PI; z+=EPS*100) {
		double vx=v*cos(z), vy=v*sin(z);
		double h=1+EPS, pt=1.0/vx; bool f=1;
		for (int i=1; i<x; ++i) {
			int th=(int)floor(h+EPS);
			if (mabs(h-th)<EPS) --th;
			if (query(i, th, th)) { f=0; break; }
			h+=-0.5*9.8*pt*pt+vy*pt;
			vy-=pt*9.8;
			if (h<1) { f=0; break; }
		}
		if (!f||h<y) continue;
		int th=(int)floor(h+EPS);
		if (mabs(h-th)<EPS) --th;
		if (!query(x, y, th)) { 
			//printf("%.3f %.3f\n", z/PI*180, h);
			printf("Yes\n"); 
			return 0; 
		}
	}

	printf("No\n");

	return 0;
}
