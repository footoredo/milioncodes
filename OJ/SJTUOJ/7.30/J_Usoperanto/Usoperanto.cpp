#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <string>
#include <vector>

using namespace std;

typedef long long ll;

const int N = 1000006;

vector<int> sons[N];
int m[N], l[N], tp=0, stack[N];
ll len[N], sum[N], f[N], nson[N];
bool vis[N], fin[N];

bool cmp(int a, int b) {
	return len[a]<len[b];
}

ll dfs(int u) {
	ll tans=0;
	tp=0;
	stack[tp++]=u;
	while (tp) {
		int x=stack[tp-1];
		if (fin[x]) {
			--tp; continue;
		}
		if (vis[x]) {
			int tlen=sons[x].size();
			tans=0;
			f[x]+=f[sons[x][nson[x]]];
			len[x]+=len[sons[x][nson[x]++]];
			if (nson[x]==tlen) {
				sort(sons[x].begin(), sons[x].end(), cmp);
				sum[0]=0;
				for (int i=0; i<tlen-1; ++i)
					sum[i] = (!i)?(len[sons[x][i]]):(sum[i-1]+len[sons[x][i]]);
				for (int i=0; i<tlen-1; ++i)
					f[x]=f[x]+sum[i];
				fin[x]=1;
			}
			else stack[tp++]=sons[x][nson[x]];
			continue;
		}
		if (!vis[x]) {
			vis[x]=1; f[x]=0;
			int tlen=sons[x].size();
			if (!tlen) {
				fin[x]=1;
				continue;
			}
			stack[tp++]=sons[x][0];
		}
	}
	return f[u];
}

int main() {
	int n; scanf("%d", &n);
	for (int i=0; i<n; ++i) {
		scanf("%d%d", &m[i], &l[i]);
		if (l[i]!=-1) sons[l[i]].push_back(i);
		len[i]=m[i]; vis[i]=false; fin[i]=false;
		f[i]=0; nson[i]=0;
	}
	ll ans=0;
	for (int i=0; i<n; ++i)
		if (l[i]==-1&&!vis[i]) ans=ans+dfs(i);
	cout<<ans<<endl;
	return 0;
}
