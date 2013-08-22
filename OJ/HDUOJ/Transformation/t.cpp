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
inline int l(Range r) { return r.rt-r.lt+1; }
inline bool in(int p, Range r) { return p>=r.lt&&p<=r.rt; }
inline bool in(Range r1, Range r2) { return r1.lt>=r2.lt&&r1.rt<=r2.rt; }
inline bool touch(Range r1, Range r2) { return in(r1.lt, r2)||in(r1.rt, r2)||in(r2, r1); }
inline int mid(Range rg) { return MID(rg.lt, rg.rt); }
Range shift(bool d, Range rg) {
	return d?Range(mid(rg)+1, rg.rt):Range(rg.lt, mid(rg));
}

inline int lowbit(int x) { return x&(-x); }
inline int mgcd(int x, int y) { return y?mgcd(y, x%y):x; }

struct Tag {
	ll mult, add;
	Tag(): mult(1), add(0) {}
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
	inline void push(int T);
};

struct Data {
	ll s[4];
	Data() { s[0]=1; s[1]=s[2]=s[3]=0; }
	inline void update(Data c1, Data c2) { FOR(i,1,4) s[i]=(c1.s[i]+c2.s[i])%MODN; }
	inline void update(int T, int c);
};

struct STree {
	Data data; Tag tag; Range range;
	int ch[2];
} L[N];
#define CT(x, y) L[L[x].ch[y]]

inline void Tag::push(int T) {
	//printf("pushing tag int range[%d, %d]\n", L[T].range.lt, L[T].range.rt);
	Tag &c1=CT(T,0).tag, &c2=CT(T,1).tag;
	c1.multx(mult); c2.multx(mult); c1.addx(add); c2.addx(add); mult=1; add=0;
}

inline void Data::update(int T, int c) {
	Tag &t=L[T].tag;
	s[0]=1; FOR(i,1,4) s[i]=s[i]*(s[0]=s[0]*t.mult%MODN)%MODN;
	s[3]=(s[3]+c*t.add*t.add*t.add+3*t.add*t.add*s[1]+3*t.add*s[2])%MODN;
	s[2]=(s[2]+c*t.add*t.add+2*t.add*s[1])%MODN;
	s[1]=(s[1]+c*t.add)%MODN;
	t.push(T);
	//printf("updated data: %d, %d, %d\n", (int)s[1], (int)s[2], (int)s[3]);
}

int cnt=1, root;

void build(int &T, Range rg) {
	T=cnt++; L[T].range = rg; 
	L[T].ch[0]=L[T].ch[1]=0; L[T].tag=Tag(); L[T].data=Data();
	if (rg.lt<rg.rt) REP(i,2) build(L[T].ch[i], shift(i, rg));
}

void modify(int T, Range rg, int op, int x) {
	//printf("modifying range[%d, %d], required range[%d, %d]..\n", L[T].range.lt, L[T].range.rt, rg.lt, rg.rt);
	if (in(L[T].range, rg)) L[T].tag.modify(op, x); 
	else {
		L[T].data.update(T, l(L[T].range));
		REP(d, 2) if (touch(rg, CT(T,d).range)) modify(L[T].ch[d], rg, op, x);
		REP(d, 2) CT(T,d).data.update(L[T].ch[d], l(CT(T,d).range));
		L[T].data.update(CT(T,0).data, CT(T,1).data);
	}
}

ll query(int T, Range rg, int op) {
	//printf("querying range[%d, %d], required range[%d, %d]..\n", L[T].range.lt, L[T].range.rt, rg.lt, rg.rt);
	L[T].data.update(T, l(L[T].range));
	if (in(L[T].range, rg)) return L[T].data.s[op];
	else {
		ll ret=0;
		REP(d, 2) if (touch(rg, CT(T,d).range)) ret=(ret+query(L[T].ch[d], rg, op))%MODN;
		return ret;
	}
}

int n, m;

int main() {
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
