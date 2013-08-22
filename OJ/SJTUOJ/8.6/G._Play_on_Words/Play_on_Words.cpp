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

int indeg[26], outdeg[26], p[26], tot;
char tmp[1005];
bool ap[26];
//vector<int> adj[]

int findset(int u) {
	if (p[u]!=u) return p[u]=findset(p[u]);
	else return u;
}

void unionset(int u, int v) {
	int fu=findset(u), fv=findset(v);
	if (fu==fv) return;
	p[fv] = fu; --tot;
}

bool check() {
	bool c=1;
	int a=0, b=0;
	REP(i, 26) {
		if (outdeg[i]==indeg[i]-1) {
			c=0;
			++a;
		}
		else if (indeg[i]==outdeg[i]-1){
			c=0;
			++b;
		}
		else if (indeg[i]!=outdeg[i]) {
			return 0;
		}
	}
	if (c) return 1;
	if (a==1&&b==1) return 1;
	return 0;
}

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		int n; scanf("%d", &n);
		tot=0;
		REP(i, 26) {
			//adj[i].clear();
			indeg[i] = 0;
			outdeg[i] = 0;
			p[i] = i;
			ap[i]=0;
		}
		REP(i, n) {
			scanf("%s", tmp);
			//adj[tmp[0]-'a'].PB(tmp[strlen[tmp]-1]-'a');
			//adj[tmp[strlen[tmp]-1]-'a'].PB(tmp[0]-'a');
			char f = tmp[0]-'a', l = tmp[strlen(tmp)-1]-'a';
			++indeg[f];
			++outdeg[l];
			unionset(f,l);
			if (!ap[f]) ++tot; ap[f]=1;
			if (!ap[l]) ++tot; ap[l]=1;
		}
		
		//if (n==1) printf("Ordering is possible.")
		if (check()&&tot==1) printf("Ordering is possible.\n");
		else printf("The door cannot be opened.\n");
		/*if (!((i_o_1&&o_i_1)||(!i_o_1&&!o_i_1))) fail = 1;
		if (fail||tot>1) printf("The door cannot be opened.\n");
		else printf("Ordering is possible.\n");*/
	}
	return 0;
}
