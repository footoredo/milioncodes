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

const int N = 20;

int n;
vector<int> adj[N];
bool vis[N], a[N][N];

void visit(int x) {
	vis[x] = 1;
	FORIT(it, adj[x])
		if (!vis[*it]) visit(*it);
}

int main() {
	int ca=1;
	while (scanf("%d", &n), n) {
		REP(i, n) {
			adj[i].clear();
			int m; scanf("%d", &m);
			REP(j, n) a[i][j]=0;
			a[i][i]=1;
			while (m--) {
				int x; scanf("%d", &x);
				a[i][x]=1;
				//adj[x].PB(i);
			}
		}
		int ans=0;
		REP(i, n) {
			int tans=0;
			REP(j, n) tans+=a[i][j];
			GU(tans, ans);
		}
		printf("Case %d: %d\n", ca, ans);
		++ca;
	}
	return 0;
}
