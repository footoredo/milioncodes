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
inline bool cmp(int x, int y) { return x>y; }

const int N = 150005;
ll data[N], cc[N], mv[N], v[N];
int ch[N][2], tag[N], size[N];
int cnt=1, root=0;
int a[N], b[N], re[N];

inline void nt(int x, int k, int rank) {
	data[x]=a[k]; size[x]=1;
	tag[x]=(rand()<<15)+rand();
	mv[x]=v[x]=re[k]-rank;
//if (v[x]<0||rank>75000) printf("Bad.\n");
}

inline void push(int x) {
	if (!x) {
		cc[x]=size[x]=0;
		mv[0]=v[0]=2000000000;
		return;
	}
	if (!cc[x]) return;
//if (cc[x]<-70000) printf("%I64d\n",cc[x]);
	cc[ch[x][0]]+=cc[x]; cc[ch[x][1]]+=cc[x];
	v[x]+=cc[x]; mv[x]+=cc[x]; cc[x]=0;
//if (v[x]<0) printf("Bad.\n");
}

inline void update(int x) {
	push(ch[x][0]); push(ch[x][1]);
	size[x]=size[ch[x][0]]+size[ch[x][1]]+1;
	mv[x]=min(v[x],min(mv[ch[x][0]],mv[ch[x][1]]));
}

int rot(int x, bool d) {
	int y=ch[x][d]; push(y);
	ch[x][d]=ch[y][!d]; ch[y][!d]=x;
	update(x); update(y); return y;
}

void ins(int &x, int k, int r) {
	if (!x) nt(x=cnt++,k,r);
	else {
		push(x);
		bool d=a[k]>data[x];
//if (d>1||d<0) printf("Bad.\n");
		cc[ch[x][1]]-=!d; v[x]-=!d;
		ins(ch[x][d],k,r+(size[ch[x][0]]+1)*d);
		update(x); if (tag[ch[x][d]]>tag[x]) x=rot(x,d);
	}
}

int tl(int x) {
	if (ch[x][0]||ch[x][1]) {
		push(x);
		bool d=tag[ch[x][1]]>tag[ch[x][0]];
		//printf("%d\n",d);
		x=rot(x,d); ch[x][!d]=tl(ch[x][!d]); 
		update(x); return x;
	} else return 0;
}

void del(int &x, int key) {
	push(x);
	if (key==data[x]) { ++cc[ch[x][1]]; x=tl(x); }
	else {
		bool d=key>data[x];
		cc[ch[x][1]]+=!d; v[x]+=!d;
		del(ch[x][d],key); update(x);
	}
}

void p(int x) {
	update(x);
	//printf("v=%d, mv=%d, data=%d.\n",v[x],mv[x],data[x]);
	REP(d,2) if (ch[x][d]) {
		printf("%d(%d)->%d(%d)\n",x,data[x],ch[x][d],data[ch[x][d]]);
		p(ch[x][d]);
	}
}

int main() {
//freopen("Input","r",stdin);
	tag[0]=-1; mv[0]=v[0]=2000000000;
	memset(cc,0,sizeof(cc));
	int n, len, h; scanf("%d%d%d", &n, &len, &h);
	REP(i,len) scanf("%d", &b[i]); sort(b,b+len,cmp);
	REP(i,n) {
		scanf("%d", &a[i]);
		int l=-1, r=len;
		while (l+1<r) {
			int m=(l+r)>>1;
			if (a[i]+b[m]<h) r=m; else l=m;
		} re[i]=l;
		if (i<len) ins(root,i,0);
	} int ans=0;
	REP(i,n-len+1) {
		//p(root);
		//printf("%d %d %d\n\n", mv[root], root, data[root]);
		ans+=mv[root]>=0;
		del(root,a[i]);
		if (i<n-len) ins(root,i+len,0);
	} printf("%d\n", ans);
	return 0;
}
/*
10 5 10
5 7 2 3 3
5 1 5 6 10 12 8 3 3 100
*/
