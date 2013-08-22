#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <string>

using namespace std;

const int MODN = 1000000007;

typedef long long ll;

ll pow2(int p) {
	if (p==0) return 1;
	if (p==1) return 2;
	ll t = pow2(p>>1);
	t = (t*t)%MODN;
	if (p&1) t=(t<<1)%MODN;
	return t;
}

ll solve(int n) {
	if (n==0) return 1;
	if (n<0) return 0;
	ll t=pow2(n-1);
	return ((t*n%MODN)+t*2)%MODN;
}

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		int n, k; scanf("%d%d", &n, &k);
		ll ans=solve(n-k)-solve(n-k-1);
		printf("%I64d\n",(ans+MODN*2)%MODN);
	}
	return 0;
}
