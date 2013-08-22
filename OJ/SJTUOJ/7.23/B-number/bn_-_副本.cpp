#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

int bs[7000006], req[1000006];
int s[12];

int main() {
	freopen("bn.in", "r", stdin);
	int n, maxn=-1, rlen=0;
	while (scanf("%d", &n)!=EOF) {
		req[rlen++] = n;
		if (n>maxn) maxn = n;
	}
	int lim=10, cnt=1;
	bs[0] = 13;
	int k=10;
	while (13*k<=n) {
		bs[cnt++]=13*k;
		k*=10; 
	}
	for (int i=2; lim*100<=n; ++i) {
		if (i==13) {
			printf("");
		}
		if (lim<=i) lim*=10;
		int t=i, l=0;
		while (t) {
			s[l++] = t%10;
			t/=10;
		}
		t=lim; int p=l-1;
		while (t) {
			if (p<l-1) if (s[p]==3&&s[p+1]==1) break;
			int r = i%t;
			int num = (i-r)*100+r+13*t;
			if (num/13*13==num) bs[cnt++] = num;
			if (p==l-1&&r/13*13==r) {
				int tt=t*10, tn;
				while ((tn=13*tt+r)<=n) {
					bs[cnt++] = tn;
					tt*=10;
				}
			}
			--p;
			t/=10;
		}
	}
	//search(0);
	sort(bs, bs+cnt);
	for (int i=0; i<rlen; ++i) {
		int n = req[i];
		if (n<13) {
			printf("0\n");
			continue;
		}
		int l=0, r=cnt;
		while (l<r-1) {
			int mid = (l+r)/2;
			if (bs[mid]>n) r=mid;
			else if (bs[mid]<n) l=mid;
			else {
				l=mid; break;
			}
 		}
 		printf("%d\n", l+1);
	}
	return 0;
}
