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
#include <iomanip>

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

ll x[1000006], y[1000006];
int tx[1000006], ty[1000006];

int main() {
	int T; scanf("%d", &T);
	cout.setf(ios::fixed);
	cout.precision(2);
	while (T--) {
		int n; scanf("%d", &n);
		REP(i, n) scanf("%d%d", &tx[i], &ty[i]);
		REP(i, n) { x[i]=tx[i]; y[i]=ty[i]; }
		x[n]=x[0], y[n]=y[0];
		ll A=0, Cx=0, Cy=0;
		REP(i, n) {
			A+=x[i]*y[i+1]-y[i]*x[i+1];
			Cx+=(x[i]+x[i+1])*(x[i]*y[i+1]-y[i]*x[i+1]);
			Cy+=(y[i]+y[i+1])*(x[i]*y[i+1]-y[i]*x[i+1]);
		}
		cout<<Cx/3.0/A<<" "<<Cy/3.0/A<<endl;
		//printf("%.2lf %.2lf\n", Cx/3.0/A, Cy/3.0/A);
	}
	return 0;
}
