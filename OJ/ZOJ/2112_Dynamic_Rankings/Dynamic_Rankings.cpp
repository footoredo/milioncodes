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
#define SZ(a) a.size()

inline int lowbit(int x) { return x&(-x); }
inline int mgcd(int x, int y) { return y?mgcd(y, x%y):x; }

typedef pair<int, int> Range;
#define LE first
#define RI second
inline int mid(Range rg) { return MID(rg.LE, rg.RI); }

inline Range cr(bool d, Range rg) {
	return d?range(mid(rg)+1, rg.RI):range(rg.LE, mid(rg));
}

struct Tree{
	Range rg;
	int ch[2], sum;
} T[N*30];

int cnt=1, n, Tn;

void build(Range rg) {
	int x=cnt++, mid=MID(l, r);
	T[x].rg = rg;
	if (l<r) REP(d, 2) T[x].ch[d]=build(cr(d, rg));
	return x;
}

int _insert(int y, int p, int val) {
	int x=cnt++; Range rg = T[y].rg; bool d;
	T[x]=T[y]; T[x].sum+=val;
	T[x].ch[d=p>mid(rg)]=insert(T[y].ch[d], p, val);
}

void insert(int p, int val) {
	for (; p<=n; C[p]=_insert(C[p], p, val), p+=lowbit(p));
}

struct Pack{
    vector L;
    inline Pack() {}
    inline Pack(int x) { L.PB(x); }
    inline void operator += (int x) { L.PB(x); }
    inline operator int() const{
        int ret = 0; REP(i, SZ(L)) res += T[T[L[i]].ch[0]].sum;
        return ret;
    }
    void shift(bool d) { REP(i, SZ(L)) L[i] = T[L[i]].ch[d]; }
};

void _query(int p) {
	Pack ret; for (; p; ret+=C[p], p-=lowbit(p));
	return ret;
}

int query(Range rg, int k) {
	Pack A=_query(rg.LE-1), B=_query(rg.RE), C=S[rg.LE-1], D=S[rg.RE];
	Range tr(0, Tn); bool d;
	for (; tr.LE<tr.RI; tr=cr(d, tr)) {
		d = A-B+C-D<k;
		A.shift(d); B.shift(d); C.shift(d); D.shift(d);
	}
	return tr.LE;
}

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		int n, m
	} 
	return 0;
}

/* need clearing:
*/
