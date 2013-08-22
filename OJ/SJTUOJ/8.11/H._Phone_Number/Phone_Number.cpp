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

ll f[55][10];
int a[55];
char number[55];

int main() {
	scanf("%s", number);
	int n=strlen(number);
	REP(i, n) a[i]=number[i]-'0';
	REP(i, 10) f[n-1][i] = 1;
	bool ff=1;
	REP(i, n-1) {
		if ((a[i]+a[i+1])&1) 
			if (a[i+1]==(a[i]+a[i+1])/2||a[i+1]==(a[i]+a[i+1])/2+1)
				continue;
			else;
		else if (a[i+1]==(a[i]+a[i+1])/2) continue;
		ff=0; break;
	}
	for (int i=n-2; i>=0; --i)
		REP(j, 10)
			if ((a[i+1]+j)&1)
				f[i][j]=f[i+1][(a[i+1]+j)/2]+f[i+1][(a[i+1]+j)/2+1];
			else f[i][j]=f[i+1][(a[i+1]+j)/2];
	ll ans=0;
	REP(i, 10) ans+=f[0][i];
	cout<<ans-ff<<endl;
	return 0;
}
