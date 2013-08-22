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
#define ll first
#define rr second
inline bool in(int p, Range r) { return p>=r.ll&&p<=r.rr; }
inline bool in(Range r1, Range r2) { return r1.ll>=r2.ll&&r1.rr<=r2.rr; }
inline int mid(Range rg) { return MID(rg.ll, rg.rr); }
Range shift(bool d, Range rg) {
	return d?Range(mid(rg)+1, rg.rr):Range(rg.ll, mid(rg));
}

inline int lowbit(int x) { return x&(-x); }
inline int mgcd(int x, int y) { return y?mgcd(y, x%y):x; }

const int BN = 1003, N = 2000006;

int T, p[BN], nxt[N], pre[N], pren[N], tj[N];
char B[BN], A[N];
bool ap[N];

int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	while (scanf("%d%s", &T, B)!=EOF) {
		int l = 0, j, n=strlen(B), fst; getchar();
		p[0]=j=-1;
		FOR(i, 1, n) {
			while (j+1&&B[j+1]!=B[i]) j=p[j];
			if (B[j+1]==B[i]) ++j;
			p[i]=j;
		}
		REP(q, T) {
			gets(A); l=strlen(A);
			REP(i, l) { nxt[i]=i+1; pre[i]=i-1; }
			j=-1; fst = 0;
			for (int i=0, k=0; i<l; i=nxt[i], ++k) {
				while (j+1&&B[j+1]!=A[i]) j=p[j];
				if (B[j+1]==A[i]) ++j;
				if (k<n) pren[i]=-1;
				else if (k==n) pren[i]=fst;
				else pren[i]=nxt[pren[pre[i]]];
				tj[i] = j;
				if (j==n-1) {
					if (pren[i]==-1) {
						fst = nxt[i];
						j = -1;
					}
					else {
						j = tj[pren[i]];
						nxt[pren[i]] = nxt[i];
					}
					pre[nxt[i]] = pren[i];
					k-=n;
				}
			}
			for (int i=fst; i<l; i=nxt[i]) putchar(A[i]);
			putchar('\n');
		}
		/*REP(i, l) ap[i]=0;

		j=-1;
		REP(i, l) {
			while (j+1&&B[j+1]!=A[i]) j=p[j];
			if (B[j+1]==A[i]) ++j;
			if (j==n-1) ap[i-n+1]=1;
		}
		REP(i, l)
			if (ap[i]) i+=n-1;
			else putchar(A[i]);*/
	}
	return 0;
}
/*
7 BUG
print "No bugs here..."

void hello() {
BUGBUG
  printfBUG("Hello, world!\n");
}

1 ERR
wriERRERRtelERRn("Hello E-R-R");
*/
