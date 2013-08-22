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

const ll oo=900000000000000000LL;
const int N = 100005;

struct tree {
	int tag, ch[2], k;
	ll data;
	tree(): data(-oo), tag(rand()*rand()) { ch[0]=ch[1]=0; }
} mem[N];

int root=0, cnt=1, fa=-1;
bool rec, td;

inline int rot(const int T, const bool d) {
	int x=mem[T].ch[d], y=mem[x].ch[!d]; //if (x==0) return T;
	mem[T].ch[d]=y; mem[x].ch[!d]=T;
	return x;
}

int ins(int T, ll d0, int k0) {
	bool d;
	if (!T) { mem[cnt].k=k0; mem[cnt].data=d0; return cnt++; }
	mem[T].ch[d=(d0>=mem[T].data)]=ins(mem[T].ch[d], d0, k0);
	if (mem[mem[T].ch[d]].tag>mem[T].tag) T=rot(T, d);
	return T;
}

int fin(int T, ll d0, int best, bool d) {					//d==1 means find the nearest one less than it.
	if (!T) return best;
	if (d^(mem[T].data>d0)) best=T;
	return fin(mem[T].ch[!(d^(best==T))],d0,best,d);
}

inline ll mabs(ll x) {
  return (x<0)?-x:x;
}

int n;

int main() {
	while (scanf("%d", &n), n) {
		root=0; cnt=1;
		REP(i, n) mem[i].ch[0]=mem[i].ch[1]=0;
		mem[0].tag=-0x7fffffff; mem[0].data=-0x7fffffff;
		root=ins(root, 1000000000, 1);
		REP(i, n) {
			int tk, tg; scanf("%d%d", &tk, &tg);
			root=ins(root, tg, tk);
			int s=fin(root, tg-1, 0, 1), b=fin(root, tg, 0, 0);
			if (s&&mabs(mem[s].data-tg)<=mabs(mem[b].data-tg))
				printf("%d %d\n", tk, mem[s].k);
			else printf("%d %d\n", tk, mem[b].k);
		}
	}
	return 0;
}
