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

const int N = 300005;
int n, x[N], k, o[N], to[N];
ll w, v, av, sum;
vector<int> ans;

bool cmp(int a, int b) {
  return x[a]<x[b];
}

int main() {
	scanf("%d", &n);
	REP(i,n) { scanf("%d", &x[i]); o[i]=i; }
	scanf("%d", &k);
	sort(o, o+n, cmp);
	REP(i,k) {
    v+=ll(x[o[i]])*ll(i)-sum;
    sum+=x[o[i]];
  }
	av=v; w=0;
	REP(i,n-k) {
	  sum-=x[o[i]];
	  v-=sum-ll(x[o[i]])*ll(k-1);
		v+=ll(x[o[i+k]])*ll(k-1)-sum;
		sum+=x[o[i+k]];
		if (v<av) { av=v; w=i+1; }
	}
	REP(i,k) ans.push_back(o[i+w]+1);
	sort(ans.begin(), ans.end());
	REP(i,k) printf("%d ", ans[i]);
	printf("\n");
	return 0;
}

