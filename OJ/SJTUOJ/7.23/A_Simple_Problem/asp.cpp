#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;

int f[10][10][102];
char s[102];

struct D {
	int lf, rf, p;
	D(int lf0=0, int rf0=0, int p0=0): lf(lf0), rf(rf0), p(p0) {}
} Q[10004];

inline int left(int x) {
	if (!x) return 9;
	else if (x==1) return -1;
	else return x-1;
}

inline int right(int x) {
	if (x) return (x+1)%10;
	else return -1;
}

inline bool onleft(int x, int y) {
	if (x&&y) return x<y;
	if (y==0) return x;
	if (x==0) return 0;
}

int main() {
	while(scanf("%s", s)!=EOF) {
	int n = strlen(s);
	for (int i=0; i<10; ++i)
		for (int j=0; j<10; ++j)
			for (int k=0; k<=n; ++k)
				f[i][j][k] = 1000000000;
	f[5][6][0] = 0;
	int l, r;
	Q[l=0].lf = 5; Q[0].rf = 6;
	Q[0].p = 0; r=1;
	int ans=-1;
	while (l<r) {
		D td = Q[l++];
		if (td.lf==8&&td.rf==9&&td.p==9) {
			printf("");
		}
		int tf = f[td.lf][td.rf][td.p];
		D nd(left(td.lf), td.rf, td.p);
		if ((nd.lf>=0&&nd.rf>=0)&&f[nd.lf][nd.rf][nd.p]>tf+1) {
			Q[r++] = nd; f[nd.lf][nd.rf][nd.p]=tf+1;
			if (nd.p==n) { ans=tf+1; break; }
		}
		nd=D(right(td.lf), td.rf, td.p);
		if ((nd.lf>=0&&onleft(nd.lf, nd.rf))&&f[nd.lf][nd.rf][nd.p]>tf+1) {
			Q[r++] = nd; f[nd.lf][nd.rf][nd.p]=tf+1;
			if (nd.p==n) { ans=tf+1; break; }
		}
		nd=D(td.lf, left(td.rf), td.p);
		if ((nd.rf>=0&&onleft(nd.lf, nd.rf))&&f[nd.lf][nd.rf][nd.p]>tf+1) {
			Q[r++] = nd; f[nd.lf][nd.rf][nd.p]=tf+1;
			if (nd.p==n) { ans=tf+1; break; }
		}
		nd=D(td.lf, right(td.rf), td.p);
		if ((nd.rf>=0&&onleft(nd.lf, nd.rf))&&f[nd.lf][nd.rf][nd.p]>tf+1) {
			Q[r++] = nd; f[nd.lf][nd.rf][nd.p]=tf+1;
			if (nd.p==n) { ans=tf+1; break; }
		}
		/*nd=D(td.lf, left(td.rf), td.p);
		if ((nd.rf>0&&onleft(nd.lf, nd.rf))&&f[nd.lf][nd.rf][nd.p]>tf+1) {
			Q[r++] = nd; f[nd.lf][nd.rf][nd.p]=tf+1;
			if (nd.p==n) { ans=tf+1; break; }
		}*/
		nd=D(left(td.lf), left(td.rf), td.p);
		if ((nd.lf>=0&&nd.rf>=0)&&f[nd.lf][nd.rf][nd.p]>tf+1) {
			Q[r++] = nd; f[nd.lf][nd.rf][nd.p]=tf+1;
			if (nd.p==n) { ans=tf+1; break; }
		}
		nd=D(left(td.lf), right(td.rf), td.p);
		if ((nd.lf>=0&&nd.rf>=0)&&f[nd.lf][nd.rf][nd.p]>tf+1) {
			Q[r++] = nd; f[nd.lf][nd.rf][nd.p]=tf+1;
			if (nd.p==n) { ans=tf+1; break; }
		}
		nd=D(right(td.lf), left(td.rf), td.p);
		if ((nd.lf>=0&&nd.rf>=0)&&(onleft(nd.lf,nd.rf)&&f[nd.lf][nd.rf][nd.p]>tf+1)) {
			Q[r++] = nd; f[nd.lf][nd.rf][nd.p]=tf+1;
			if (nd.p==n) { ans=tf+1; break; }
		}
		nd=D(right(td.lf), right(td.rf), td.p);
		if ((nd.lf>=0&&nd.rf>=0)&&f[nd.lf][nd.rf][nd.p]>tf+1) {
			Q[r++] = nd; f[nd.lf][nd.rf][nd.p]=tf+1;
			if (nd.p==n) { ans=tf+1; break; }
		}
		if (td.lf==s[td.p]-'0') {
			if (f[td.lf][td.rf][td.p+1]>tf+1) {
				Q[r++]=D(td.lf, td.rf, td.p+1);
				f[td.lf][td.rf][td.p+1]=tf+1;
				if (td.p==n-1) { ans=tf+1; break; }
			}
			nd=D(td.lf, left(td.rf), td.p+1);
			if ((nd.rf>=0&&onleft(nd.lf, nd.rf))&&f[nd.lf][nd.rf][nd.p]>tf+1) {
				Q[r++] = nd; f[nd.lf][nd.rf][nd.p]=tf+1;
				if (nd.p==n) { ans=tf+1; break; }
			}
			nd=D(td.lf, right(td.rf), td.p+1);
			if (nd.rf>=0&&f[nd.lf][nd.rf][nd.p]>tf+1) {
				Q[r++] = nd; f[nd.lf][nd.rf][nd.p]=tf+1;
				if (nd.p==n) { ans=tf+1; break; }
			}
		}
		if (td.rf==s[td.p]-'0') {
			if (f[td.lf][td.rf][td.p+1]>tf+1) {
				Q[r++]=D(td.lf, td.rf, td.p+1);
				f[td.lf][td.rf][td.p+1]=tf+1;
				if (td.p==n-1) { ans=tf+1; break; }
			}
			nd=D(right(td.lf), td.rf, td.p+1);
			if ((nd.lf>=0&&onleft(nd.lf, nd.rf))&&f[nd.lf][nd.rf][nd.p]>tf+1) {
				Q[r++] = nd; f[nd.lf][nd.rf][nd.p]=tf+1;
				if (nd.p==n) { ans=tf+1; break; }
			}
			nd=D(left(td.lf), td.rf, td.p+1);
			if (nd.lf>=0&&f[nd.lf][nd.rf][nd.p]>tf+1) {
				Q[r++] = nd; f[nd.lf][nd.rf][nd.p]=tf+1;
				if (nd.p==n) { ans=tf+1; break; }
			}
		}
	}
	printf("%d\n", ans);
	}
	return 0;
}
