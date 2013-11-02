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

typedef pair<int, int> Range;
#define lt first
#define rt second
inline bool in(int p, Range r) { return p>=r.lt&&p<=r.rt; }
inline bool in(Range r1, Range r2) { return r1.lt>=r2.lt&&r1.rt<=r2.rt; }
inline int mid(Range rg) { return MID(rg.lt, rg.rt); }
Range shift(bool d, Range rg) {
	return d?Range(mid(rg)+1, rg.rt):Range(rg.lt, mid(rg));
}

const int MODN =10000007;

ll x;
bool num[60];
int len;
ll ans[60],c[60][60], fans=1;

ll mpow(ll a, ll p) {
  if (a==1) return 1;
  if (p==0) return 1;
  if (p==1) return a%MODN;
  ll tp=mpow(a,p>>1);
  return (((tp*mpow(a,p&1))%MODN)*tp)%MODN;
}

int main() {
	cin>>x;
	while (x) {
		num[len++] = x%2;
		x/=2;
	}
	c[0][0]=1;
	for (int i=1; i<len; ++i)
		for (int j=0; j<=i; ++j)
			c[i][j]=(j?c[i-1][j-1]:0)+c[i-1][j];
	int cc=0;
	for (int i=len-1; i>=0; --i) if (num[i]) {
		REP(j,i+1) ans[cc+j]+=c[i][j];
		++cc;
	}
  ++ans[cc];
  //ans[cc-num[0]]=(ans[cc-num[0]]+1)%MODN;
	REP(i, len+1) {
    fans=fans*mpow(i+1,ans[i+1])%MODN;
    //cout<<i+1<<' '<<mpow(i+1,ans[i+1])<<endl;
  }
	cout<<fans<<endl;
	return 0;
}
