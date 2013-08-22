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

inline int mmax(int x, int y) { return x<y?y:x; }
inline int lowbit(int x) { return x&(-x); }
inline int mgcd(int x, int y) { return y?mgcd(y, x%y):x; }

const int N=600005, K=5;
int n, k, pos[N][K], as[N][1<<K], x, od[N];
multiset<int> se[1<<K];
__typeof(se[0].begin()) i1, i2;

void ins(int i) {
	for(int a=0;a<(1<<k);a++) {
   		as[i][a]=0;
    	for(int j=0;j<k;j++) {
        	if(a&(1<<j))as[i][a]+=pos[i][j];
        	else as[i][a]-=pos[i][j];
    	}
    	se[a].insert(as[i][a]);
	}
}

int query() {
	int ans=0;
	for(int a=0; a<(1<<k); a++) {
   		i1=se[a].begin();
    	i2=se[a].end();
    	i2--;
    	ans=mmax(ans,(*i2)-(*i1));
	}
	return ans;
}

void del(int x) {
	REP(a, 1<<k) {
		i1=se[a].find(as[x][a]);
		se[a].erase(i1);
	}
	od[x]=1;
}

int main() {
	while (~scanf("%d%d", &n, &k)) {
		REP(i, n) {
			scanf("%d", &od[i]);
			if (od[i]) {
				scanf("%d", &x);
				del(x-1);
			}
			else {
				REP(j, k) scanf("%d", &pos[i][j]);
				ins(i);
			}
			printf("%d\n", query());
		}
		REP(i, n) if (!od[i]) del(i);
	}
	return 0;
}
