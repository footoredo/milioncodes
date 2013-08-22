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
inline int mabs(int x) { return x<0?-x:x; }

typedef pair<int, int> Monk;

set<Monk> monks1, monks2;

int main() {
	while (scanf("%d", &n), n) {
		monks1.insert(Monk(1000000000, 1));
		monks2.insert(Monk(-1000000000, 1));
		REP(i, n) {
			int k, g; scanf("%d%d", &k, &g);
			Monk monk1 = monks1.lower_bound(g);
			Monk monk2 = monks2.lower_bound(-g);
			monks1.insert(Monk(g, k));
			monks2.insert(Monk(-g, k));
			if (Monk monk1 mabs(g-Monk1.first)<mabs())
		}
	}
	return 0;
}
