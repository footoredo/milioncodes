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

const int N = 502, W = 10004;

int val[N], wei[N];
int f[W];

struct Coin {
	double t;
	int no;
} coin[N];

bool cmp(Coin a, Coin b) {
	return a.t>b.t;
}

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		int x, w; scanf("%d%d", &x, &w); w-=x;
		int n; scanf("%d", &n); int cnt=1;
		FOREQ(i, 1, n) {
			int vi, wi;
			scanf("%d%d", &val[i], &wei[i]);
			/*coin[i].t = wei[i]*1.0/val[i];
			coin[i].no = i;*/
			/*int tot = w/wi, b;
			for (b=1; b<tot; b<<=1) {
				val[++cnt]=vi*b;
				wei[cnt]=wi*b;
				tot-=b;
			}
			val[++cnt]=vi*tot;
			wei[cnt]=wi*tot;*/
		}
		/*sort(coin+1, coin+1+n, cmp);
		MEMSET(f, -1);
		f[0][0] = 0;
		bool now = 1;
		FOREQ(i, 1, cnt)
			FOREQ(j, 0, w) {
				f[now][j] = f[!now][j];
				if (wei[i]<=j&&f[!now][j-wei[i]]!=-1)
					if (f[now][j]==-1||f[now][j]>f[!now][j-wei[i]]+val[i])
					f[now][j] = f[!now][j-wei[i]]+val[i];
				now = !now;
			}
		if (f[!now][w]==-1) printf("This is impossible.\n");
		else printf("The minimum amount of money in the piggy-bank is %d.\n",f[!now][w]);
	}*/
	MEMSET(f, 127);
	f[0] = 0;
	FOREQ(i, 1, n)
		REP(j, w+1)
			if (j>=wei[i])
				f[j]=min(f[j], f[j-wei[i]]+val[i]);
	if (f[w]==2139062143) printf("This is impossible.\n");
		else printf("The minimum amount of money in the piggy-bank is %d.\n",f[w]);
	}
	return 0;
}
