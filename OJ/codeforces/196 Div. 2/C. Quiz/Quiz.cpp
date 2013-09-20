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
const int MODN = 1000000009;

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

ll p2(int b) {
	if (b==0) return 1; 
	if (b==1) return 2;
	ll t=p2(b>>1);
	return t*t%MODN*p2(b&1)%MODN;	
}

int main() {
	ll n,m,k; cin>>n>>m>>k;
	ll m1=m-(n-m)*(k-1);
	if (m1<=0) { cout<<m<<endl; return 0; }
	ll p=m-m1, ans=((k*p2(m1/k+1)%MODN)%MODN-k*2+m1%k+p+MODN*2)%MODN;
	cout<<ans<<endl;
	return 0;
}
