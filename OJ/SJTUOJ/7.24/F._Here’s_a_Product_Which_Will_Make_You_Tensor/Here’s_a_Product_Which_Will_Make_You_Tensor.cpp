#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <string>
#include <cmath>

using namespace std;

typedef long long ll;

const int N = 602;

int n, m, qa[N], pa[N];
int ma[N][N], qc, pc, tmd[N][N];

inline bool eq(double a, double b) {
	return abs(a-b)<0.00001;
}

int mgcd(int a, int b) {
	int r;
	while (r=a%b) {
		a = b; b = r;
	}
	return b;
}

int main() {
	while (scanf("%d%d", &n, &m), n&&m) {
		for (int i=1; i<=n; ++i)
			for (int j=1; j<=m; ++j)
				scanf("%d", &ma[i][j]);
		int ans=0; qc=pc=0;
		for (int q=1; q*q<=m; ++q)
			if (m/q*q==m)
				if (q*q==m)
					qa[qc++] = q;
				else {
					qa[qc++] = q;
					qa[qc++] = m/q;
				}
		for (int q=1; q*q<=n; ++q)
			if (n/q*q==n)
				if (q*q==n)
					pa[pc++] = q;
				else {
					pa[pc++] = q;
					pa[pc++] = n/q;
				}
		for (int k=0; k<pc; ++k)
			for (int l=0; l<qc; ++l) {
				int p=pa[k], q=qa[l];
				if ((p==1&&q==1)||(p==n&&q==m)) continue;
				bool flag = 0, one=0;
				for (int i=1; i<=p; ++i)
					for (int j=1; j<=q; ++j)
						tmd[i][j] = ma[i][j];
				for (int i=1; !flag&&i<=n; i+=p)
					for (int j=1; j<=n; j+=q) {
						double s = 1.0*ma[i][j]/ma[1][1];
						int maxt = 1, tt;
						for (int ti=i; !flag&&ti-i<p; ++ti)
							for (int tj=j; tj-j<q; ++tj) {
								if (!eq(1.0*ma[ti][tj]/ma[ti-i+1][tj-j+1],s)) {
									flag = 1;
									break;
								}
								if (!one) {
									tmd[ti-i+1][tj-j+1]=mgcd(tmd[ti-i+1][tj-j+1],ma[ti][tj]);
									if (tmd[ti-i+1][tj-j+1]==1) one=1;
									/*if ((tt=ma[ti][tj]/tmd[ti-i+1][tj-j+1])>maxt)
										maxt = tt;*/
								}
							}
						if (flag) break;
						/*for (int ti=i; !one&&ti-i<p; ++ti)
							for (int tj=j; !one&&tj-j<q; ++tj) {
								tmd[ti-i+1][tj-j+1]=ma[ti][tj]/maxt;
									if (tmd[ti-i+1][tj-j+1]==1) {
										one=1; break;
									}
							}*/
					}
				if (!flag) {
					int addation = 1;
					if (!one) {
						int k = rand()%(n/p), l = rand()%(m/q);
						int maxt = ma[k*p+1][l*p+1]/tmd[1][1], tt;
						for (int ti=k*p+1; !one&&ti-k*p<=p; ++ti)
							for (int tj=l*q+1; !one&&tj-l*q<=q; ++tj)
								if ((tt=ma[ti][tj]/tmd[ti-k*p][tj-l*q])>maxt)
									maxt = tt;
						for (int ti=k*p+1; !one&&ti-k*p<=p; ++ti)
							for (int tj=l*q+1; !one&&tj-l*q<=q; ++tj) {
								tmd[ti-k*p][tj-l*q]=ma[ti][tj]/maxt;
								if (tmd[ti][tj]==1) {
									one=1; break;
								}
							}
					}
					if (!one) {
						int t = tmd[1][1];
						for (int i=1; i<=p; ++i)
							for (int j=1; j<=q; ++j)
								t = mgcd(t, tmd[i][j]);
						for (int i=2; i<=t; ++i)
							if (t/i*i==t) ++addation;
					}
					ans += addation;
				}
			}
		printf("%d\n", ans);
	}
	return 0;
}
