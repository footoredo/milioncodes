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

bool check(int A, int B, double X, double Y) {
	if (A>B+EPS) swap(A, B);
	if (X>Y+EPS) swap(X, Y);
	return X+EPS<A&&Y+EPS<B;
}

const int S = 1;
int A, B;
double X, Y;

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		cin>>A>>B>>X>>Y;
		bool res=0;
		REP(i, 90*S) {
			double a = Y*sin(i*1.0/S*PI/180.0);
			double b = sqrt(Y*Y-a*a);
			if (check(A,B,a+b/Y*X,b+a/Y*X)) {
				res = 1; break;
			}
		}
		if (res) printf("Escape is possible.\n");
		else printf("Box cannot be dropped.\n");
	}
	return 0;
}
