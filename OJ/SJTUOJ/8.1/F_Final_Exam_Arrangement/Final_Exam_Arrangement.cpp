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

const int N = 100005;

struct Exam {
	int order;
	int s, t;
} exams[N];

vector<int> day[N];

bool cmp(Exam a, Exam b) {
	if (a.s==b.s)
		return a.t>b.t;
	else return a.s<b.s;
}

int main() {
	int n;
	while (scanf("%d", &n)!=EOF) {
		REP(i, n) day[i+1].clear();
		REP(i, n) {
			scanf("%d%d", &exams[i].s, &exams[i].t);
			exams[i].order = i+1;
		}
		sort(exams, exams+n, cmp);
		int l=exams[0].s, r=exams[0].t, p=1;
		day[p].push_back(exams[0].order);
		FOR(i, 1, n) {
			if (exams[i].s<r) {
				l=exams[i].s;
				r=min(r, exams[i].t);
			}
			else {
				++p;
				l=exams[i].s;
				r=exams[i].t;
			}
			day[p].push_back(exams[i].order);
		}
		printf("%d\n", p);
		FOREQ(i, 1, p) {
			printf("%d", day[i][0]);
			FOR(j, 1, day[i].size())
				printf(" %d", day[i][j]);
			printf("\n");
		}
		printf("\n");
	}
	return 0;
}
