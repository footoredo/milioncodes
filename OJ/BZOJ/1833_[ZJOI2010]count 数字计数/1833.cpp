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

ll ans[2][10];
ll ta[20][2], p10[20];
int di[20], c;

void solve(bool k, ll x) {
  if (x==0) {
    ans[k][0]=1;
    return;
  }
  else if (x==-1) return;
  c=0; ll tx=x;
  while (x) {
    di[c++]=x%10;
    x/=10;
  }
  ll t=0;
  for (int i=c-1; i>=0; --i) {
    t=t+di[i]*p10[i];
    ans[k][di[i]]+=tx-t+1;
    REP(j,di[i]) if (j||(c-i-1)||!j&&!(c-1)) ans[k][j]+=p10[i];
    REP(j,10) ans[k][j]+=ta[i][1]*di[i];
    if (i==c-1) ans[k][0]+=-ta[i][1]+ta[i][0];
  }
}

int main() {
  ll k=1, t=0; p10[0]=1;
	REP(i,18) {
	  ta[i+1][1]=k*(i+1); ta[i+1][0]=ta[i+1][1]-t;
	  k*=10; t+=k;
	  p10[i+1]=k;
	} ta[1][0]=1;
	ll a,b; cin>>a>>b; --a;
	solve(0,a); solve(1,b);
	REP(i,9) cout<<ans[1][i]-ans[0][i]<<" ";
	cout<<ans[1][9]-ans[0][9]<<endl;
	return 0;
}
