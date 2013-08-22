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
static const double EPS = 1e-8;
static const double PI = acos(-1.0);

#define REP(i, n) for (int i = 0; i < (int)(n); i++)
#define FOR(i, s, n) for (int i = (s); i < (int)(n); i++)
#define FOREQ(i, s, n) for (int i = (s); i <= (int)(n); i++)
#define FORIT(it, c) for (__typeof((c).begin())it = (c).begin(); it != (c).end(); it++)
#define MEMSET(v, h) memset((v), h, sizeof(v))
#define PB push_back
#define GU(a, b) if ((a)>(b)) (b)=(a);
#define SU(a, b) if ((a)<(b)) (b)=(a);

const int N = 100005;

struct Data {
	int v, s, l, no;
	double tc;
	Data(int v0=0, int s0=0, int l0=0):v(v0),s(s0),l(l0) {}
};

int n, m, T;
vector<Data> adj[N];
queue<int> Q;
bool inq[N];
double d[N];
int len[N], pr[N], e[N];

double gett(double limit, Data d) {
	return d.l*1.0/(d.s+limit);
}

double SPFA(double limit, int s, int t) {
	FOREQ(i, 1, n)
		d[i] = 1000000000;
	d[s] = pr[s] = 0; len[s] = 1;
	Q.push(s); inq[s] = 1;
	while (!Q.empty()) {
		int u = Q.front(), v; Q.pop();
		double t;
		inq[u] = 0;
		FORIT(it, adj[u]) {
			if ((t=d[u]+gett(limit, *it))<d[v=it->v]) {
				d[v] = t;
				pr[v] = u;
				len[v] = len[u]+1;
				e[v] = it->no;
				if (!inq[v]) {
					inq[v] = 1;
					Q.push(v);
				}
			}
		}
	}
	return d[n];
}

int ansl[N];

int main() {
	scanf("%d%d", &n, &m);
	REP(i, m) {
		Data td;
		int u, v;
		scanf("%d%d%d%d", &u, &v, &td.s, &td.l);
		td.no = i+1;
		td.v=v; adj[u].PB(td);
		td.v=u; adj[v].PB(td);
	}
	scanf("%d", &T);
	double l=0, r=50000000;
	while (l+EPS<r) {
		double mid = (l+r)/2.0;
		double tans=SPFA(mid, 1, n);
		if (tans<=T) r = mid;
		else l = mid;
	}
	printf("%.6lf", r);
	SPFA(r, 1, n);
	printf(" %d\n", len[n]-1);
	int tlen = len[n];
	int t = n; ansl[--tlen] = e[t];
	while (pr[t]) ansl[--tlen] = e[t = pr[t]];
	REP(i, len[n]-2) printf("%d ", ansl[i+1]);
	printf("%d\n",ansl[len[n]-1]);
	return 0;
}
