#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>

using namespace std;

const int N = 102;

vector<int> adj[N];
bool vis[N];

void dfs(int x) {
	vis[x] = 1; int v;
	for (int i=0; i<adj[x].size(); ++i)
		if (!vis[v=adj[x][i]])
			dfs(v);
	printf("%d ", x);
}

int main() {
	int n; scanf("%d", &n);
	for (int i=1; i<=n; ++i) {
		int x;
		while (scanf("%d", &x), x)
			adj[x].push_back(i);
	}
	for (int i=1; i<=n; ++i)
		if (!vis[i]) dfs(i);
	printf("\n");
	return 0;
}
