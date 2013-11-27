#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <cmath>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

typedef long long ll;
#define REP(i,n) for (int i=0; i<n; ++i)
const string filename="time";

inline void setIO() {
  freopen((filename+".in").c_str(), "r", stdin);
  freopen((filename+".out").c_str(), "w", stdout);
}

const int N = 1003;
struct Edge {
	int v, l, r;
	Edge(int v, int l, int r): v(v), l(l), r(r) {}
};
vector<Edge> adj[N];
vector<int> pool;
int n, m;

queue<int> Q;
bool vis[N];
bool check(int bl, int br) {
  if (br<bl) return 1;
	while (!Q.empty()) Q.pop();
	memset(vis, 0, sizeof vis);
	Q.push(0); vis[0]=1;
	while (!Q.empty()) {
		int u=Q.front(), s=adj[u].size(); Q.pop();
		if (u==n-1) return 1;
		REP(i,s) {
			Edge &e = adj[u][i];
			if (e.l>bl||e.r<br) continue;
			if (!vis[e.v]) {
				if (e.v==n-1) return 1;
        vis[e.v]=1;
				Q.push(e.v);
			}
		}
	}
	return 0;
}

int main() {
  scanf("%d%d", &n, &m);
  if (!m) {
    printf("Nice work, Dima!\n");
    return 0;
  }
  REP(i,m) {
  	int a, b, c, d;
  	scanf("%d%d%d%d", &a, &b, &c, &d);
  	--a; --b; pool.push_back(c); pool.push_back(d);
  	adj[a].push_back(Edge(b,c,d));
  	adj[b].push_back(Edge(a,c,d));
  }
  sort(pool.begin(), pool.end());
  int ans = 0;
  REP(i,pool.size()-1) {
    int l=i-1, r=pool.size(), mid;
    while (l+1<r)
      if (check(pool[i],pool[mid=l+r>>1])) l=mid; else r=mid;
    if (l>i) if (pool[l]-pool[i]+1>ans) ans=pool[l]-pool[i]+1;
  }
  if (!ans) printf("Nice work, Dima!\n");
  else printf("%d\n", ans);
  return 0;
}

