#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <string>
#include <vector>

using namespace std;

typedef long long ll;

const int N = 100000;

int n, m, pos[N], ind[N];
vector<int> adj[N];
bool ced[N];

void go(int ti, int p) {
	for (int i=1; i<=n; )
}

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &m);
		for (int i=1; i<=n; ++i) {
			scanf("%d", &pos[i]);
			adj[i].clear();
		}
		memset(ced, 0, sizeof ced);
		memset(ind, 0, sizeof ind);
		while (m--) {
			int i, j; scanf("%d%d", &i, &j);
			adj[i].push_back(j);
			++ind[j];
		}
		memcpy(tid, ind, sizeof ind);
		go(0, 1);
		memcpy(tid, ind, sizeof ind);
		memset(ced, 0, sizeof ced);
		go(0, 2);
	}
	return 0;
}
