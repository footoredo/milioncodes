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

int n, m;
bool seq[100];

bool check() {
	int len=0, ret=0;
	REP(i, n)
		if (seq[i]) ++len;
		else {
			if (len>ret) ret=len;
			len=0;
		}
	if (len>ret) ret=len;
	return ret>=m;
}

int ans=0;

void fuck(int dep) {
	if (dep>n) {
		ans = (ans+check())%1000000007;
	}
	else {
		seq[dep-1]=0; fuck(dep+1);
		seq[dep-1]=1; fuck(dep+1);
	}
}

int main() {
	for (n=2; n<=10; ++n)
		for (m=0; m<=n; ++m) {
	ans=0;
	fuck(1);
	printf("n=%d,m=%d,ans=%d\n",n, m, ans);
}
	return 0;
}
