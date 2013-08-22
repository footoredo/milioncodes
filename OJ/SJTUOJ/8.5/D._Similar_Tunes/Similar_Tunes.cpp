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

int T[128];
int n, m;
int a[N], b[N];
char note[5];

int solve(char note[5]) {
	int t1 = note[0]-'0';
	int t2 = T[note[1]];
	if (note[2]=='+') ++t2;
	else if (note[2]=='-') --t2;
	return (t1-1)*12+t2;
}

int main() {
	T['C']=0; T['D']=2; T['E']=4; T['F']=5;
	T['G']=7; T['A']=9; T['B']=11;
	scanf("%d", &n);
	REP(i, n) {
		scanf("%s", note);
		a[i] = solve(note);
	}
	scanf("%d", &m);
	REP(q, m) {
		int le;
		scanf("%d", &le);
		REP(i, le) {
			scanf("%s", note);
			b[i] = solve(note);
		}
		int l=1-le, r=0, shift=le-1, ans=0;
		for (; l<n; ++l, ++r, --shift) {
			int tl=max(0, l), tr=min(n-1, r);
			int tans=0;
			FOREQ(i, tl, tr)
				tans+=a[i]==b[i+shift];
			GU(tans, ans);
		}
		printf("%.6lf\n", ans*1.0/le);
	}
	return 0;
}
