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
const int N = 100005;

#define REP(i, n) for (int i = 0; i < (int)(n); i++)
#define FOR(i, s, n) for (int i = (s); i < (int)(n); i++)
#define FOREQ(i, s, n) for (int i = (s); i <= (int)(n); i++)
#define FORIT(it, c) for (__typeof((c).begin())it = (c).begin(); it != (c).end(); it++)
#define MEMSET(v, h) memset((v), h, sizeof(v))
#define PB push_back
#define GU(a, b) if ((a)>(b)) (b)=(a);
#define SU(a, b) if ((a)<(b)) (b)=(a);
#define MID(a, b) (((a)+(b))>>1)

int n, m;
string s[N];
char tmp[N], b[N];
int next[N], ans[N], fans[N];

int get_next(char *b) {
	next[0]=-1;
	int j=-1, m=strlen(b);
	FOREQ(i, 1, m-1) {
		while (j>=0&&b[j+1]!=b[i]) j=next[j];
		if (b[j+1]==b[i]) ++j;
		next[i]=j;
	}
}

int _check(char *b, int *p, int k) {
	int j=-1, n=s[k].length(), m=strlen(b);
	REP(i, n-2+m) {
		while (j>=0&&b[j+1]!=s[k][i]) j=next[j];
		if (b[j+1]==s[k][i]) ++j;
		if (j==m-1) return i-m+2;
	}
	return 0;
}

bool check(int l) {
	for (int i=0; i<m; ++i) {
		strncpy(b, s[0].c_str()+i, l);
		get_next(b);
		bool checked = 1;
		ans[0]=i+1;
		int p;
		for (int j=1; j<n; ++j)
			if (!(p=_check(b, next, j))) {
				checked = 0;
				break;
			}
			else ans[j]=p;
		if (checked) return 1;
	}
	return 0;
}

int main() {
	scanf("%d%d", &n, &m);
	REP(i, n) {
		scanf("%s", tmp);
		s[i]=string(tmp)+string(tmp);
	}
	if (n==1) {
		printf("%d\n1", m);
		return 0;
	}
	int l=0, r=m+1;
	while (l<r) {
		int mid = MID(l, r);
		if (check(mid)) {
			l=mid;
			memcpy(fans, ans, sizeof ans);
		}
		else r=mid;
	}
	printf("%d\n", l);
	REP(i, n) printf("%d\n", fans[i]);
	return 0;
}

/*
4 4
caba
bbba
abab
caab
*/
