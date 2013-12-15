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

typedef pair<int, int> Range;
#define lt first
#define rt second
inline bool in(int p, Range r) { return p>=r.lt&&p<=r.rt; }
inline bool in(Range r1, Range r2) { return r1.lt>=r2.lt&&r1.rt<=r2.rt; }
inline int mid(Range rg) { return MID(rg.lt, rg.rt); }
Range shift(bool d, Range rg) {
	return d?Range(mid(rg)+1, rg.rt):Range(rg.lt, mid(rg));
}

inline int lowbit(int x) { return x&(-x); }
inline int mgcd(int x, int y) { return y?mgcd(y, x%y):x; }

const int N = 500005;
int s[N], l, r, n, ans, le[N];
bool tak[N];
int f[N][2];

int main() {
	scanf("%d", &n);
	REP(i,n) scanf("%d", &s[i]);
	sort(s, s+n);
	l=-1;
	REP(i,n) {
	  while (l<i-1&&s[l+1]*2<=s[i]) ++l;
	  le[i]=l+1;
	}
	ans=0; int t=-100000000;
	REP(i,n) if (i) {
	  f[i][0]=f[i-1][1];
	  if (le[i-1]<le[i]) {
	    f[i][1]=max(f[i-1][0], f[i-1][1]);
	    if (le[i]=le[i-1]+1) f[i][0]=f[i-1][0]+1;
	    else f[i][0]=-100000000;
	  }
	  else {
	    f[i][1]=f[i-1][1]; f[i][0]=f[i-1][0];
	    if (f[i-1][1]==le[i]-1) f[i][0]=f[i-1][1]+1;
	    else f[i][1]=f[i-1][1]+1;
	  }
	}
	else { f[i][0]=0; f[i][1]=-100000000; }
	printf("%d\n", n-max(f[n-1][0],f[n-1][1]));
	return 0;
}
