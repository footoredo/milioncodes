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

const int N = 502;

string tmp;
map<string, bool> hash;
vector<int> g[N];
vector<vector<int> > ans;
int f[N], n;

void trail(int p, vector<int> route) {
	route.PB(p);
	if (g[p].size())
		FORIT(it, g[p])
			trail(*it, route);
	else {
		vector<int> tans;
		for (int t=route.size()-1; t>=0; --t)
			tans.PB(route[t]);
		ans.PB(tans);
	}
}

int main() {
	for (int i=0; i<26; ++i) {
		string t = ""; t+=char(i+'a');
		hash[t]=1;
		t = ""; t+=char(i+'A');
		hash[t]=1;
	}
	while (getline(cin, tmp), tmp.size()>1) {
		hash[tmp]=1;
		//cout<<int(tmp[0])<<endl;
	}
	while (getline(cin, tmp), tmp.size()>1) {
		n = tmp.length();
		f[0]=1;
		for (int i=1; i<n; ++i) {
			f[i]=f[i-1]+1;
			g[i].clear();
			if (hash[tmp.substr(0, i+1)]) {
				f[i]=1;
				continue;
			}
			for (int j=1; j<i; ++j)
				if (f[j-1]+1<f[i]&&hash[tmp.substr(j,i-j+1)])
					f[i]=f[j-1]+1;
			for (int j=1; j<=i; ++j)
				if (f[j-1]+1==f[i]&&hash[tmp.substr(j,i-j+1)])
					g[i].PB(j-1);
		}
		ans.clear();
		trail(n-1, vector<int>());
		sort(ans.begin(), ans.end());
		printf("%d %d\n", ans.size(), f[n-1]);
		FORIT(it, ans) {
			int p=0;
			//FORIT(jt, *it) printf("%d ", *jt);
			//printf("\n");
			FORIT(jt, *it) {
				while ((p<n)&&(*jt!=p-1)) printf("%c", tmp[p++]);
				if (p<n) printf(" ");
			}
			while (p<n) printf("%c", tmp[p++]);
			printf("\n");
		}
	}
	return 0;
}
