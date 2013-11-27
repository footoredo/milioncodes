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

typedef pair<int, int> Range;
#define lt first
#define rt second
inline bool in(int p, Range r) { return p>=r.lt&&p<=r.rt; }
inline bool in(Range r1, Range r2) { return r1.lt>=r2.lt&&r1.rt<=r2.rt; }
inline int mid(Range rg) { return MID(rg.lt, rg.rt); }
Range shift(bool d, Range rg) {
	return d?Range(mid(rg)+1, rg.rt):Range(rg.lt, mid(rg));
}

inline int lowbit(int x) { return x&(-x); }
inline int mgcd(int x, int y) { return y?mgcd(y, x%y):x; }
inline int mabs(int x) { return x<0?-x:x; }

const int N = 2003, INF = 100000008;

int n, m, k, s, a[N][N], root, q[100005];
int maxd[10][10], p[10][2][N], d[N], cnt, data[N*2], lt[N*2], rt[N*2], tag[N*2], ch[N*2][2], ans[10][10];

void buildt(int &T, int l, int r) {
	T=cnt++; tag[T]=0; lt[T]=l; rt[T]=r;
	if (l==r) {
		ch[T][0]=ch[T][1]=0;
		data[T]=d[l];
		return;
	}
	buildt(ch[T][0], l, l+r>>1);
	buildt(ch[T][1], (l+r>>1)+1, r);
	data[T]=max(data[ch[T][0]],data[ch[T][1]]);
}

inline void push(int T) {
	tag[ch[T][0]]+=tag[T]; tag[ch[T][1]]+=tag[T];
	data[ch[T][0]]+=tag[T]; data[ch[T][1]]+=tag[T];
	tag[T]=0;
}

void modi(int T, int l, int r, int d) {
	if (lt[T]>=l&&rt[T]<=r) {
		tag[T]+=d; data[T]+=d;
		return;
	}
	int mid=lt[T]+rt[T]>>1; push(T);
	if (l<=mid) modi(ch[T][0],l,r,d);
	if (r>mid) modi(ch[T][1],l,r,d);
	data[T]=max(data[ch[T][0]],data[ch[T][1]]);
}

int query(int T, int l, int r) {
	if (lt[T]>=l&&rt[T]<=r) return data[T];
	int mid=lt[T]+rt[T]>>1; push(T);
	if (l<=mid) query(ch[T][0],l,r);
	if (r>mid) query(ch[T][1],l,r);
	return max(data[T], max(data[ch[T][0]], data[ch[T][1]]));
}

int main() {
	scanf("%d%d%d%d", &n, &m, &k, &s);
	REP(i,n) REP(j,9) { p[j][0][i]=INF; p[j][1][i]=-INF; }
	REP(i,n) REP(j,m) {
		scanf("%d", &a[i][j]); --a[i][j];
		GU(j,p[a[i][j]][1][i]);
		SU(j,p[a[i][j]][0][i]);
	}
	REP(i,9) REP(j,9) ans[i][j]=-INF;
	REP(k,9) {
		REP(j,m) {
			REP(i,n) {
				if (p[k][0][i]==INF) d[i]=-INF;
				else d[i]=max(mabs(p[k][0][i]-j),mabs(p[k][1][i]-j))+i;
			}
			cnt=1; root=0; int t;
			buildt(root,0,n-1);
			REP(i,n) {
				if ((t=query(root,0,n-1))>ans[k][a[i][j]])
					ans[k][a[i][j]]=t;
				if (i==n-1) break;
				modi(root,0,i,1); modi(root,i+1,n-1,-1);
			}
		}
	}
	int fa=-INF;
	REP(i,s) {
		scanf("%d", &q[i]);
		if (i) GU(ans[q[i-1]-1][q[i]-1],fa);
	}
	printf("%d\n", fa);
	return 0;
}
