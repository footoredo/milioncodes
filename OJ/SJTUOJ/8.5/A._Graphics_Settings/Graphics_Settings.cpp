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

const ll oo=900000000000000000LL;
const int N = 500005;

struct tree {
	int tag, ch[2];
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

int ins(int T, ll d0) {
	bool d;
	if (!T) { mem[cnt].data=d0; return cnt++; }
	mem[T].ch[d=(d0>=mem[T].data)]=ins(mem[T].ch[d], d0);
	if (mem[mem[T].ch[d]].tag>mem[T].tag) T=rot(T, d);
	return T;
}

int fin(int T, ll d0, int best, bool d) {					//d==1 means find the nearest one less than it.
	if (!T) return best;
	if (d^(mem[T].data>d0)) best=T;
	return fin(mem[T].ch[!(d^(best==T))],d0,best,d);
}

int del(int T, ll todel) {
	int ret=T; bool d;
	if (todel==mem[T].data) {
		if (!(mem[T].ch[0]||mem[T].ch[1])) return 0;
		ret=rot(T, d=(mem[mem[T].ch[0]].tag<mem[mem[T].ch[1]].tag));
		mem[ret].ch[!d]=del(T,todel);
	}
	else mem[T].ch[d=todel>mem[T].data]=del(mem[T].ch[d],todel);
	return ret;
}

inline ll mabs(ll x) {
  return (x<0)?-x:x;
}

const int VAL = 30;
map<string, int> pars;
char tmp[20], op[20];
int w, h, p, n, m;
int f[N];
bool on[N];

ll visit(int T) {
	if (!T) return 1;
	ll ret = f[mem[T].data];
	if (ret>p) return p+1;
	ret=ret*visit(mem[T].ch[0]);
	if (ret>p) return p+1;
	ret=ret*visit(mem[T].ch[1]);
	if (ret>p) return p+1;
	return ret;
}

ll solve() {
	ll t = visit(root);
	if (t>p) return 0;
	return p/t/w/h;
}

int main() {
	scanf("%d", &n);
	srand(223133); mem[0].tag=-0x7fffffff;
	REP(i, n) {
		int t;
		scanf("%s%d", tmp, &t);
		pars[string(tmp)]=i;
		root=ins(root, i);
		f[i] = t;
		on[i] = 1;
	}
	scanf("%d%d%d%d", &w, &h, &p, &m);
	int k;
	if (n<=VAL) {
					ll frame = solve();
					if (frame<10) printf("Slideshow\n");
					else if (frame>=60) printf("Perfect\n");
					else printf("So-so\n");
				}
				else printf("Slideshow\n");
	REP(q, m) {
		scanf("%s", op);
		switch (op[1]) {
			case 'n':
				scanf("%s", tmp);
				k = pars[string(tmp)];
				if (!on[k]) {
				root=ins(root, k);
				++n;}
				on[k] = 1;
				if (n<=VAL) {
					double frame = solve();
					if (frame<10) printf("Slideshow\n");
					else if (frame>=60) printf("Perfect\n");
					else printf("So-so\n");
				}
				else printf("Slideshow\n");
				break;
			case 'f':
				scanf("%s", tmp);
				k = pars[string(tmp)];
				if (on[k]) {
				root=del(root, k);
				--n; }
				on[k] = 0;
				if (n<=VAL) {
					double frame = solve();
					if (frame<10) printf("Slideshow\n");
					else if (frame>=60) printf("Perfect\n");
					else printf("So-so\n");
				}
				else printf("Slideshow\n");
				break;
			case 'e':
				scanf("%d%d", &w, &h);
				if (n<=VAL) {
					double frame = solve();
					if (frame<10) printf("Slideshow\n");
					else if (frame>=60) printf("Perfect\n");
					else printf("So-so\n");
				}
				else printf("Slideshow\n");
				break;
		}
	}
	return 0;
}
