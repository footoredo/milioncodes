#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <string>

using namespace std;

typedef long long ll;

ll b[102], f[102], s[102];
int n, divi[21], tn[102];

void init(ll x) {
	int k;
	b[k=0] = 1; s[0]=0;
	while (b[k]<=x) {
		b[k+1]=b[k]<<1; ++k;
		if (k==6) {
			printf("");
		}
		f[k]=1; int t = k;
		for (int i=2; i<=t&&i+i<=k; ++i)
			if (t/i*i==t) {
				f[k]+=b[i-1]-1;
				while (t/i*i==t) t/=i;
			}
		if (k==1) f[k]=0;
		s[k]=s[k-1]+f[k];
	}
	n = k;
}

ll sum(ll x) {
	if (!x) return 0;
	int l=0, ox=x;
	while (x) {
		tn[l++] = x&1;
		x>>=1;
	}
	ll ret = s[l-1];
	if (b[l]-1==ox) ++ret;
	int t = l, cnt=0;
	for (int i=2; i<=t&&i+i<=l; ++i)
		if (t/i*i==t) {
			ll k=0, kk=0;
			for (int j=0; j<i; ++j)
				k=(k<<1)+tn[l-1-j];
			kk=k;
			for (int j=1; j<l/i; ++j)
				kk=(kk<<i)+k;
			if (kk<=ox) ++ret;
			divi[cnt++] = i;
			while (t/i*i==t) t/=i;
		}
	for (int i=l-2; i>=0; --i)
		if (tn[i])
			for (int j=0; j<cnt; ++j)
				if (divi[j]>=l-i)
					ret += b[divi[j]-l+i];
	return ret;
}

int main() {
	ll l, r; cin>>l>>r;
	init(r);
	cout<<sum(r)-sum(l-1)<<endl;
	return 0;
}
