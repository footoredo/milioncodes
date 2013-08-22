#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

int bs[7000006], req[1000006], tbs[10000007];
int s[12], tcnt, cnt;

void search(int dep, int n) {
	if (dep==7) {
		int t=1;
		for (int i=7; i>=0; --i) {
			//if ((i<7)&&(s[i]==1&&s[i+1]==3)) return;
			if (t>n&&n/13*13!=n) return;
			int h = n/t*t;
			int num = h*100+n-h+13*t;
			if (num/13*13==num) tbs[++tcnt-1]=num;
			t*=10;
		}
	}
	else {
		for (int i=0; i<10; ++i) {
			//s[dep] = i;
			search(dep+1, n*10+i);
		}
	}
}

int main() {
	freopen("bn.in", "r", stdin);
	int n, maxn=-1, rlen=0;
	while (scanf("%d", &n)!=EOF) {
		req[rlen++] = n;
		if (n>maxn) maxn = n;
	}
	search(0, 0);
	sort(tbs, tbs+tcnt);
	for (int i=0; i<tcnt; ++i)
		if (!i||(i&&tbs[i]!=tbs[i-1]))
			bs[cnt++] = tbs[i];
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
