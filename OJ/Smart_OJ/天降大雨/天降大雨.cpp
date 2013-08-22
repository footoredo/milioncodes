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

int n;
char m[15], s[10004];

int main() {
	while (scanf("%d%s%s", &n, m, s), n) {
		bool rain = 0;
		REP(i, strlen(s)-n+1) {
			bool flag = 1;
			REP(j, n)
				if (m[j]!=s[i+j]) {
					flag = 0;
					break;
				}
			if (flag) {
				rain = 1;
				break;
			}
		}
		if (rain) printf("rain\n");
		else printf("sun\n");
	}
	return 0;
}
