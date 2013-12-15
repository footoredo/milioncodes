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
static const double EPS = 1e-5;
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
inline double mabs(double x) { return x>0?x:-x; }

const string filename = "points";
inline void setIO() {
	freopen((filename+".in").c_str(), "r", stdin);
	freopen((filename+".out").c_str(), "w", stdout);
}

const int N = 50004;
int k, n, x[N], y[N], a[N], b[N];
typedef pair<double,double> S;
S A[N], B[N*2];
int fail[N], ss;

inline bool eq(S a, S b) {
	return mabs(a.first-b.first)<EPS&&mabs(a.second-b.second)<EPS;
}

void init() {
	fail[0]=ss-1; int j=ss-1;
	for (int i=ss+1; i<k; ++i) {
		while (j!=ss-1&&!eq(A[j+1],A[i])) j=fail[j];
		if (eq(A[j+1],A[i])) ++j;
		fail[i]=j;
	}
}

inline double d(int x, int y, double a, double b) {
  return sqrt((x-a)*(x-a)+(y-b)*(y-b));
}

int getS(S *A, int *x, int *y, int k) {
	double x0=0, y0=0, l=0; int s=0;
	REP(i,k) { scanf("%d%d", &x[i], &y[i]); x0+=x[i]; y0+=y[i]; }
	x0/=k; y0/=k;
	REP(i,k) {
		if (mabs(y[i]-y0)<EPS&&mabs(x[i]-x0)<EPS) {
			A[i]=make_pair(-1,0); ++s; continue;
		}
		A[i]=make_pair(atan2(y[i]-y0,x[i]-x0),d(x[i],y[i],x0,y0));
		if (A[i].second>l) l=A[i].second;
		while (A[i].first<0) A[i].first+=2*PI;
	}
	REP(i,k) A[i].second/=l;
	sort(A,A+k); double last=A[k-1].first;
	for (int i=k-1; i-s; --i) A[i].first-=A[i-1].first;
	A[s].first-=last-2*PI;
	return s;
}

int main() {
  //setIO();
	scanf("%d", &k);
	ss=getS(A,x,y,k); init();

	scanf("%d", &n);
	while (n--) {
	  int tk; scanf("%d", &tk);
		int ts=getS(B,a,b,tk);
		if (ts!=ss||tk!=k) {
			printf("No\n");
			continue;
		}
		REP(i,k-ts) B[i+k]=B[i+ts];
		int j=ss-1; bool Y=0;
		for (int i=ss; i<k*2-ts; ++i) {
			while (j>ss-1&&!eq(A[j+1],B[i])) j=fail[j];
			if (eq(A[j+1],B[i])) ++j;
			if (j==k-1) {
			  printf("Yes\n");
				Y=1; break;
			}
		}
		if (!Y) {
		  reverse(B+ss,B+k);
		  double f=B[ss].second;
		  for (int i=ss; i<k-1; ++i) B[i].second=B[i+1].second; B[k-1].second=f;
		  /*reverse(B+k,B+k*2-ss);
		  f=B[k*2-ss-1].second;
		  for (int i=k; i<k*2-ss; ++i) B[i].second=B[i-1].second; B[k].second=f;*/
		  REP(i,k-ts) B[i+k]=B[i+ts];
		  j=ss-1;
		  for (int i=ss; i<k*2-ts; ++i) {
			  while (j>ss-1&&!eq(A[j+1],B[i])) j=fail[j];
			  if (eq(A[j+1],B[i])) ++j;
			  if (j==k-1) {
			    printf("Yes\n");
				  Y=1; break;
			  }
		  }
		  if (!Y) printf("No\n");
		}
	}

	return 0;
}
