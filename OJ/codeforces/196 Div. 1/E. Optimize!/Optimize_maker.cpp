#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>

#define REP(i, n) for (int i = 0; i < (int)(n); i++)
#define FOR(i, s, n) for (int i = (s); i < (int)(n); i++)
#define FOREQ(i, s, n) for (int i = (s); i <= (int)(n); i++)
#define FORIT(it, c) for (__typeof((c).begin())it = (c).begin(); it != (c).end(); it++)
#define MEMSET(v, h) memset((v), h, sizeof(v))
#define PB push_back
#define GU(a, b) if ((a)>(b)) (b)=(a);
#define SU(a, b) if ((a)<(b)) (b)=(a);
#define MID(l, r) (((l)+(r))>>1)

using namespace std;

int main() {
	srand(time(0));
	freopen("Input","w",stdout);
	printf("150000 75000 1\n");
	REP(i,75000) printf("%d ",(rand()+(rand()<<15))%1000000000+1);
	printf("\n");
	REP(i,150000) printf("%d ",(rand()+(rand()<<15))%1000000000+1);
	printf("\n");
	return 0;
}
