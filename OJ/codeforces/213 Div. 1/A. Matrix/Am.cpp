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

const int N = 4003;

ll cnt[N*10], sum[N], ans;
char num[N];

int main() {
	int a, l; scanf("%d%s", &a, num); l=strlen(num);
	REP(i,l) {
		sum[i]=num[i]-'0';
		if (i) sum[i]+=sum[i-1];
		++cnt[sum[i]];
	}
	REP(i,l) REP(j,i) ++cnt[sum[i]-sum[j]];
	if (a==0) {
		REP(i,sum[l-1]+1) ans+=cnt[0]*cnt[i]*2;
		ans-=cnt[0]*cnt[0];
		cout<<ans<<endl;
		return 0;
	}
	ll ta=sum[l-1]?(a/sum[l-1]):1;
	for (int x=max(1LL,ta); x*x<=a&&x<=sum[l-1]; ++x) if (a/x*x==a) {
		if (x*x==a) ans+=cnt[x]*cnt[x];
		else ans+=cnt[x]*cnt[a/x]*2;
	}
	cout<<ans<<endl;
	return 0;
}
