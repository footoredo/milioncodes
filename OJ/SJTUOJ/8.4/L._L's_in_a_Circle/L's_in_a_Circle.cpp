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
static const double EPS = 1e-10;
static const double PI = acos(-1.0);

#define REP(i, n) for (int i = 0; i < (int)(n); i++)
#define FOR(i, s, n) for (int i = (s); i < (int)(n); i++)
#define FOREQ(i, s, n) for (int i = (s); i <= (int)(n); i++)
#define FORIT(it, c) for (__typeof((c).begin())it = (c).begin(); it != (c).end(); it++)
#define MEMSET(v, h) memset((v), h, sizeof(v))
#define PB push_back
#define GU(a, b) if ((a)>(b)) (b)=(a);
#define SU(a, b) if ((a)<(b)) (b)=(a);

double a, b, c, r, t;
const double T=2.6405593003588292;

bool check(double r) {
	b=sqrt(r*r-1.0*a*a)-2.0*a;
	c=sqrt(r*r-(2.0*a-b)*(2.0*a-b))-2.0*a;
	t=0.5*a*a+(1.5*sqrt(2)*a-c-b+1.0*a)*(1.5*sqrt(2)*a-c-b+1.0*a);
	return t>r*r;
}

int main() {
	a=10000.0;
	double l=26400.0, r=26410.0;
	while (r-l>EPS) {
		double mid = (l+r)/2.0;
		if (check(mid)) l = mid;
		else r = mid;
	}
	printf("%.12lf", l);
	/*while (cin>>a, a>-0.5)
	 	printf("%.10lf\n", a*T);*/
	return 0;
}
