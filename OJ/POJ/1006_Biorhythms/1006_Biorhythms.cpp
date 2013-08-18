#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

int mabs(int x) {
	if (x<0) return -x;
	else return x;
}

int main() {
	int p, e, i, d, ca=1;
	while (scanf("%d%d%d%d", &p, &e, &i, &d), p+1) {
		for (int ans=1; ans<=21252; ++ans)
			if (!(((mabs(ans+d-p)%23)||(mabs(ans+d-e)%28))||(mabs(ans+d-i)%33))) {
				printf("Case %d: the next triple peak occurs in %d days.\n", ca, ans);
				break;
			}
		++ca;
	}
	return 0;
}
