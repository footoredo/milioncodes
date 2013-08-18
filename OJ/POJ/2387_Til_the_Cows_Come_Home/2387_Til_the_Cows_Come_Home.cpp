#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

using namespace std;

const int N = 1003;

struct Data {
	int v, w;
	Data(int v0=0, int w0=0): v(v0), w(w0) {}
};

int t, n;
vector<Data> adj[N];
int dist[N], size, pos[N], heap[N];
bool out[N];

void diving(int *h, int x) {
	for (int nxt; (nxt=x<<1)<=size; x=nxt) {
		if (nxt<size&&dist[h[nxt]]>dist[h[nxt+1]]) ++nxt;
		if (dist[h[nxt]]>=dist[h[x]]) return;
		swap(h[x], h[nxt]);
		swap(pos[h[x]], pos[h[nxt]]);
	}
}

void floating(int *h, int x) {
	for (int nxt; nxt=x>>1; x=nxt) {
		if (dist[h[nxt]]<=dist[h[x]]) return;
		swap(h[x], h[nxt]);
		swap(pos[h[x]], pos[h[nxt]]);
	}
}

int mpop(int *h) {
	int ret = h[1];
	swap(h[1], h[size--]);
	pos[h[1]] = 1;
	diving(h, 1);
	return ret;
}

int dik(int s, int t) {
	memset(dist, 127, sizeof dist);
	memset(out, 0, sizeof out);
	dist[s] = 0;
	for (int i=1; i<=n; ++i) { heap[i] = i; pos[i] = i; }
	size = n;
	swap(heap[1], heap[s]); swap(pos[1], pos[s]);
	for (;;) {
		int u = mpop(heap), v;
		if (u==t) return dist[u];
		out[u] = 1;
		for (int i=0; i<adj[u].size(); ++i)
			if (!out[v=adj[u][i].v]&&dist[v]>dist[u]+adj[u][i].w) {
				dist[v] = dist[u]+adj[u][i].w;
				floating(heap, pos[v]);
			}
	}
}

int main() {
	scanf("%d%d", &t, &n);
	while (t--) {
		int u, v, w; scanf("%d%d%d", &u, &v, &w);
		adj[u].push_back(Data(v, w));
		adj[v].push_back(Data(u, w));
	}
	printf("%d\n", dik(1, n));
	return 0;
}
/*
5 5
1 2 20
2 3 30
3 4 20
4 5 20
1 5 100
*/
