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

inline int lowbit(int x) { return x&(-x); }
inline int mgcd(int x, int y) { return y?mgcd(y, x%y):x; }

const int N = 1003;

typedef pair<int, int> Pos;

char gra[N][N];
int ans[N][N], cnt=1, n, m, col[N][N];
bool inv[N][N], qed[N][N];
queue<Pos> Q;

int main() {
	scanf("%d%d", &n, &m);
	REP(i, n) { getchar(); REP(j, m) gra[i+1][j+1]=getchar(); }
	REP(i, n+2) inv[i][0]=inv[i][m+1]=1;
	REP(i, m+2) inv[0][i]=inv[n+1][i]=1;
	int s=n*m;
	REP(i, n) REP(j, m) {
		if (gra[i+1][j+1]=='.') { --s; inv[i+1][j+1]=1; }
		//if (gra[i+1][j+1]=='w') inv[i+1][j+1]=1;
	}
	bool ok=1; 
	REP(i, n) REP(j, m) if (gra[i+1][j+1]=='b') {
		int t=(gra[i][j+1]!='w'||gra[i+2][j+1]!='w')+(gra[i+1][j]!='w'||gra[i+1][j+2]!='w');
		if (t==2) { ok=0; break; }
		if (t==1) { qed[i+1][j+1]=1; Q.push(Pos(i+1, j+1)); }
	}
	if (!ok) { printf("NO\n"); return 0; }
	while (!Q.empty()) {
		Pos t = Q.front(); Q.pop();
		int x=t.first, y=t.second; s-=3;
		int tt=(inv[x-1][y]||inv[x+1][y])+(inv[x][y-1]||inv[x][y+1]);
		if (tt==2) { ok=0; break; }
		if (inv[x-1][y]||inv[x+1][y]) {
			ans[x][y-1]=ans[x][y]=ans[x][y+1]=cnt++;
			inv[x][y-1]=inv[x][y]=inv[x][y+1]=1;
			if (!qed[x-1][y-1]&&!inv[x-1][y-1]&&gra[x-1][y-1]=='b') { Q.push(Pos(x-1, y-1)); qed[x-1][y-1]=1; }
			if (!qed[x+1][y-1]&&!inv[x+1][y-1]&&gra[x+1][y-1]=='b') { Q.push(Pos(x+1, y-1)); qed[x+1][y-1]=1; }
			if (!qed[x+1][y+1]&&!inv[x+1][y+1]&&gra[x+1][y+1]=='b') { Q.push(Pos(x+1, y+1)); qed[x+1][y+1]=1; }
			if (!qed[x-1][y+1]&&!inv[x-1][y+1]&&gra[x-1][y+1]=='b') { Q.push(Pos(x-1, y+1)); qed[x-1][y+1]=1; }
			if (y-2>0&&!qed[x][y-2]&&!inv[x][y-2]&&gra[x][y-2]=='b') { Q.push(Pos(x, y-2)); qed[x][y-2]=1; }
			if (y+2<=m&&!qed[x][y+2]&&!inv[x][y+2]&&gra[x][y+2]=='b') { Q.push(Pos(x, y+2)); qed[x][y+2]=1; }
		}
		else {
			ans[x-1][y]=ans[x][y]=ans[x+1][y]=cnt++;
			inv[x-1][y]=inv[x][y]=inv[x+1][y]=1;
			if (!qed[x-1][y-1]&&!inv[x-1][y-1]&&gra[x-1][y-1]=='b') { Q.push(Pos(x-1, y-1)); qed[x-1][y-1]=1; }
			if (!qed[x+1][y-1]&&!inv[x+1][y-1]&&gra[x+1][y-1]=='b') { Q.push(Pos(x+1, y-1)); qed[x+1][y-1]=1; }
			if (!qed[x+1][y+1]&&!inv[x+1][y+1]&&gra[x+1][y+1]=='b') { Q.push(Pos(x+1, y+1)); qed[x+1][y+1]=1; }
			if (!qed[x-1][y+1]&&!inv[x-1][y+1]&&gra[x-1][y+1]=='b') { Q.push(Pos(x-1, y+1)); qed[x-1][y+1]=1; }
			if (x-2>0&&!qed[x-2][y]&&!inv[x-2][y]&&gra[x-2][y]=='b') { Q.push(Pos(x-2, y)); qed[x-2][y]=1; }
			if (x+2<=m&&!qed[x+2][y]&&!inv[x+2][y]&&gra[x+2][y]=='b') { Q.push(Pos(x+2, y)); qed[x+2][y]=1; }
		}
	}
	bool c[5];
	REP(i, n) {
		REP(j, m)
			if (ans[i+1][j+1]&&!col[i+1][j+1]) {
				c[0]=1;
				c[1]=c[2]=c[3]=c[4]=0;
				int x=i+1, y=j+1;
				if (ans[x][y+1]==ans[x][y]) {
					for (int k=y; k<=y+2&&k<=m; ++k) 
						c[col[x-1][k]]=c[col[x+1][k]]=1;
					c[col[x][y-1]]=1;
					c[col[x][y+3]]=1;
					REP(k, 5) if (!c[k]) { 
						col[x][y]=col[x][y+1]=col[x][y+2]=k; break; 
					}
				}
				else {
					for (int k=x; k<=x+2&&k<=n; ++k) 
						c[col[k][y-1]]=c[col[k][y+1]]=1;
					c[col[x-1][y]]=1;
					c[col[x+3][y]]=1;
					REP(k, 5) if (!c[k]) { 
						col[x][y]=col[x+1][y]=col[x+2][y]=k; break; 
					}
				}
			}
	}
	if (s||!ok) {
		printf("NO\n");
		return 0;
	}
	printf("YES\n");
	REP(_, n) {
		REP(__, m)
			if (!col[_+1][__+1]) printf(".");
			else printf("%c", col[_+1][__+1]+'a'-1);
		printf("\n");
	}
	return 0;
}
