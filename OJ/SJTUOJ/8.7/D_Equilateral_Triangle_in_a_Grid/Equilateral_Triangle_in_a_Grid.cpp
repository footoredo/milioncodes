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

typedef pair<double, double> pos;
#define xx first
#define yy second
#define sqr(x) ((x)*(x))

inline double dis(pos A, pos B) {
	return sqrt(sqr(A.xx-B.xx)+sqr(A.yy-B.yy));
}

inline double mabs(double x) {
	if (x>0) return x; else return -x;
}

inline bool eq(pos A, pos B) {
	return (mabs(A.xx-B.xx)<EPS&&mabs(A.yy-B.yy)<EPS);
}

inline bool check(pos A, pos B, pos C) {
	if ((eq(A, B)||eq(B, C))||eq(A, C)) return 0;
	double a=dis(C, B), b=dis(A, C), c=dis(B, A);
	/*if (a==b&&b==c) {
		printf("pA: (%.2lf, %.2lf)\n", A.xx, A.yy);
		printf("pB: (%.2lf, %.2lf)\n", B.xx, B.yy);
		printf("pC: (%.2lf, %.2lf)\n\n", C.xx, C.yy);
	}*/
	return mabs(a-b)<EPS&&mabs(b-c)<EPS;
}

const double t=sqrt(3.0);

/*pos getp(int a, int b) {
	if (!b) return a*1.0;
	else return 0;
}*/

int main() {
	int n, ans=0; scanf("%d", &n);
	
	REP(i, n) REP(j, n-i) REP(k, n) REP(l, n-k) REP(o, n) REP(p, n-o) {
		//pos A=getp(i, j), B=getp(k, l), C=getp(o, p);
		if (check(pos(i*t,j*2+i),pos(k*t,l*2+k),pos(o*t,p*2+o)))
			++ans;
	}
	printf("%d\n", ans/6);
	return 0;
}
