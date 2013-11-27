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

const int N = 200005;
int n, m, p, a[N], b[N];
int si, Q[N*5], l, r, cnt[N], tcnt[N];
map<int,bool> hash;
vector<int> pool, ans;

int main() {
  freopen("B.in", "r", stdin);
	scanf("%d%d%d", &n, &m, &p);
	if (m*p>n) {
    printf("0\n");
    return 0;
  }
	REP(i,n) { scanf("%d", &a[i]); hash[a[i]]=0; }
	REP(i,m) { scanf("%d", &b[i]); hash[b[i]]=1; pool.push_back(b[i]); }
	pool.push_back(0);
	REP(i,n) { if (!hash[a[i]]) a[i]=0; }
	sort(pool.begin(), pool.end());
	REP(i,n) a[i]=lower_bound(pool.begin(), pool.end(), a[i])-pool.begin();
	REP(i,m) b[i]=lower_bound(pool.begin(), pool.end(), b[i])-pool.begin();
	REP(i,m) ++cnt[b[i]];
	si=pool.size();
	REP(k,p) {
		l=r=0;
		REP(j,si) tcnt[j]=-cnt[j];
		REP(i,m) ++tcnt[a[k+i*p]];
		REP(i,si) if (tcnt[i]<0) Q[r++]=i;
		if (l==r) ans.push_back(k+1);
		REP(i,(n/p)-m+1) {
			int q=k+(i+1)*p;
			--tcnt[a[q-p]];
			if (tcnt[a[q-p]]<0) Q[r++]=a[q-p];
			++tcnt[a[q+(m-1)*p]];
			while (tcnt[Q[l]]>=0&&l<r) ++l;
			if (l==r) ans.push_back(q+1);
		}
	}
	sort(ans.begin(), ans.end());
	int c=ans.size(); printf("%d\n", c);
	REP(i,c) printf("%d ", ans[i]);
	printf("\n");
	return 0;
}

