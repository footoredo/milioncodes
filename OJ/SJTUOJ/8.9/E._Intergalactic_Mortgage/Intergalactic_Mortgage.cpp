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

ll x, y;
int n;
double r;

struct Mat {
	double m[2][2];
	Mat() {
		REP(i, 2) REP(j, 2) m[i][j]=0;
	}
	Mat mult(Mat t) {
		Mat ret;
		REP(i, 2) REP(j, 2) REP(k, 2)
			ret.m[i][j]+=m[k][j]*t.m[i][k];
		return ret;
	}
} one, ans, mat, fans;

Mat pow(Mat b, int p) {
	if (p==0) return one;
	if (p==1) return b;
	Mat t=pow(b,p>>1);
	return (t.mult(t)).mult(pow(b,p&1));
}

int main() {
	while (cin>>x>>y>>n>>r, x||y||n||(int)(r*100)) {
		r/=12.0*100.0;
		double rr=0, t=x, lt=x; bool yes=0;
		REP(i, 2) one.m[i][i]=1;
		ans.m[0][0]=-y; ans.m[1][0]=x;
		mat.m[0][0]=1; mat.m[0][1]=0;
		mat.m[1][0]=1; mat.m[1][1]=r+1;
		REP(i, 2) REP(j, 2) fans.m[i][j]=0;
		if (x*(r+1)-y<x) {
			mat=pow(mat, n*12);
			REP(i, 2) REP(j, 1) REP(k, 2)
				fans.m[i][j]+=ans.m[k][j]*mat.m[i][k];
			yes=fans.m[1][0]<EPS;
		}
		/*FOREQ(i, 1, n*12) {
			rr=x*(r+1)-(ll)(x*(r+1))+rr*(r+1);
			x=(ll)(x*(r+1))-y+(int)rr;
			rr-=(int)rr;
			t=t*(r+1)-y;
			if (x<0||x==0&&rr<EPSt<EPS) {
				yes = 1;
				//cout<<x<<' '<<setprecision(5)<<rr<<endl;
				break;
			}
			if (t>=lt) break;
			lt = t;
			//printf("%.5f\t%.5f\n", t, x+rr);
			cout<<setprecision(5)<<t<<'\t';
			cout<<x<<' '<<setprecision(5)<<rr<<endl;
		}*/
		if (yes) printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}
