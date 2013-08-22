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
const int N = 500005, MODN = 10007;

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
inline bool touch(Range r1, Range r2) { return in(r1.lt, r2)||in(r1.rt, r2)||in(r2, r1); }
inline int mid(Range rg) { return MID(rg.lt, rg.rt); }
Range shift(bool d, Range rg) {
	return d?Range(mid(rg)+1, rg.rt):Range(rg.lt, mid(rg));
}

inline int lowbit(int x) { return x&(-x); }
inline int mgcd(int x, int y) { return y?mgcd(y, x%y):x; }

Range range[N];
int ch[N][2];

struct Tag {
	ll mult, add;
	Tag(): mult(1), add(0) {}
	inline void init() { mult=1; add=0; }
	inline void givex(int x) { mult=0; add=x; }
	inline void addx(int x) { add=(add+x)%MODN; /*printf("\tadded tag: mult=%d, add=%d\n", mult, add);*/ }
	inline void multx(int x) {
		mult=(mult*x)%MODN;
		add=(add*x)%MODN;
		//printf("\tmulted tag: mult=%d, add=%d\n", mult, add);
	}
	inline void modify(int op, int x) {
		if (op==0) addx(x);
		else if (op==1) multx(x);
		else givex(x);
		//printf("modified tag: mult=%d, add=%d.\n", (int)mult, (int)add);
	}
	inline void push(Tag &c) { c.multx(mult); c.addx(add); }
} tag[N];

struct Data {
	ll s[4];
	Data() { REP(i,4) s[i]=0; }
	inline void init() { REP(i,4) s[i]=0; }
	inline void update(Data c) { REP(i,4) s[i]=(s[i]+c.s[i])%MODN; /*printf("\tupdated data: %d, %d, %d\n", s[1], s[2], s[3]);*/ }
	inline void update(Tag t, Range rg) {
		int c=rg.rt-rg.lt+1;
		s[0]=1; FOR(i,1,4) s[i]=s[i]*(s[0]=s[0]*t.mult%MODN)%MODN;
		s[3]=(s[3]+c*t.add*t.add*t.add+3*t.add*t.add*s[1]+3*t.add*s[2])%MODN;
		s[2]=(s[2]+c*t.add*t.add+2*t.add*s[1])%MODN;
		s[1]=(s[1]+c*t.add)%MODN;
		//printf("\tupdated data: %d, %d, %d\n", s[1], s[2], s[3]);
	}
} data[N];

inline void push(int T) {
	//printf("pushing tag on range[%d, %d]\n", range[T].lt, range[T].rt);
	REP(d,2) tag[T].push(tag[ch[T][d]]);
	data[T].update(tag[T], range[T]); tag[T].init();
}

int cnt=1, root;

void build(int &T, Range rg) {
	T=cnt++; range[T] = rg;
	ch[T][0]=ch[T][1]=0; tag[T].init(); data[T].init();
	if (rg.lt<rg.rt) REP(d,2) build(ch[T][d], shift(d, rg));
}

void modify(int T, Range rg, int op, int x) {
	//printf("modifying range[%d, %d], required range[%d, %d]..\n", range[T].lt, range[T].rt, rg.lt, rg.rt);
	if (in(range[T], rg)) tag[T].modify(op,x); 
	else {
		push(T); data[T].init();
		REP(d,2) {
			if (touch(rg, range[ch[T][d]])) modify(ch[T][d], rg, op, x); 
			//printf("modifying range[%d, %d], required range[%d, %d]..\n", range[T].lt, range[T].rt, rg.lt, rg.rt);
			push(ch[T][d]); data[T].update(data[ch[T][d]]);
		}
	}
}

ll query(int T, Range rg, int op) {
	//printf("querying range[%d, %d], required range[%d, %d]..\n", L[T].range.lt, L[T].range.rt, rg.lt, rg.rt);
	push(T); if (in(range[T], rg)) return data[T].s[op];
	else {
		ll ret=0;
		REP(d,2) if (touch(rg, range[ch[T][d]])) ret=(ret+query(ch[T][d], rg, op))%MODN;
		return ret;
	}
}

int main() {
	int n, m;
	while (scanf("%d%d", &n, &m), n||m) {
		cnt=1; build(root, Range(1, n));
		int o, x, y, c;
		REP(i, m) {
			scanf("%d%d%d%d", &o, &x, &y, &c);
			if (o<4) modify(root, Range(x, y), o-1, c);
			else printf("%d\n", (int)query(root, Range(x, y), c));
		}
	}
	return 0;
}
