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

const int N = 1000006;

int la, lb;
char a[N], b[N];
ll hash[N][26], sum[N], n, m;

int main() {
	cin>>n>>m;
	scanf("%s%s", a, b);
	if (strlen(a)>strlen(b)) {
    swap(a,b);
    swap(n,m);
  }
	la=strlen(a); lb=strlen(b);
	int g=mgcd(la,lb);
	REP(i,g) {
		int p=i;
		REP(j,lb/g) {
			++hash[i][b[p]-'a'];
			++sum[i];
			p=(p+la)%lb;
		}
	}
	ll ans=0;
	REP(i,la) {
		ans+=sum[i%g]-hash[i%g][a[i]-'a'];
	}
	cout<<ans*(n/(lb/g))<<endl;
	return 0;
}
