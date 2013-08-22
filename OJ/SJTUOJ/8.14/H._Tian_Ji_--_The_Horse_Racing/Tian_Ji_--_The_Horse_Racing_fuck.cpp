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

bool cmp(int a, int b) { return a>b; }

int tj[5003], ki[5003], n;
bool chosen[5003];

int main() {
	while (scanf("%d", &n), n) {
		REP(i, n) { chosen[i]=0; scanf("%d", &tj[i]); }
		REP(i, n) scanf("%d", &ki[i]);
		sort(tj, tj+n);
		sort(ki, ki+n, cmp);
		int p1=0, p2=0, ans=0;
		REP(i, n) {
			/*while (p2<n&&!chosen[p2]&&tj[i]<ki[p2]) ++p2;
			if (p2==n) {
				bool eq;
				for (int k=n-1; tj[i]<=ki[k]&&k>=0; --k)
					if (!chosen[k]&&tj[i]==ki[k]) {
						chosen[k]=1;
						eq=1; break;
					}
				if (eq) continue;
				while (chosen[p1]) ++p1;
				chosen[p1]=1; --ans;
				continue;
			}
			if (tj[i]==ki[p2]) {
				if (i==n-1||p2==n-1) continue;
				if (tj[i+1]<ki[p2]&&tj[i+1]>=ki[p2+1]) continue;
			}
			else {
				++ans; chosen[p2]=1;
			}*/
			bool f=0;
			REP(j, n) if (!chosen[j]&&ki[j]<=tj[i]) {
				if (ki[j]<tj[i]) ++ans;
				f=1; chosen[j]=1;
				break;
			}
			if (!f) --ans;
		}
		printf("%d\n", ans*200);
	}
	return 0;
}
