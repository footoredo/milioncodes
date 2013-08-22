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
#define MID(l, r) (((l)+(r))>>1)

const int N = 300005, MODN = 1000000007;

inline int lowbit(int x) { return x&(-x); }
inline int mgcd(int x, int y) { return y?mgcd(y, x%y):x; }

int n, m, k, a[N], t[N];
ll C[N], f[N];
bool ap[N];
ll ext_gcd(ll A,ll B,ll &x,ll &y){
  //if (A<B) return ext_gcd(B,A,y,x);
  if (B==0){
    x=1;y=0;
    return A;
  }
  ll ret=ext_gcd(B,A%B,x,y);
  ll tmp=x; x=y; y=tmp-(A/B)*y;
  //y-=x*(A/B);
  return ret;
}
void calcC() {
  for (int i=0;i<n-k;i++) C[i]=0;
  C[n-k]=1;
 ll A,B,inv,y;
 for (int i=n-k+1;i<=m;i++){
   A=i-(n-k);B=MODN;
   ext_gcd(A,B,inv,y);
   if (inv<0){
     inv=inv%B;
     inv=inv+B;
     inv=inv%B;
   }
   C[i]=(C[i-1]*i*inv)%MODN;
 }
}

ll mpow(ll p, ll b) {
	if (b==0) return 1;
	if (b==1) return p;
	ll ttt=mpow(p, b>>1); //cout<<ttt<<" "<<p<<" "<<b<<endl;
	return ttt*ttt%MODN*mpow(p, b&1)%MODN;
}

int main() {
	while (~scanf("%d%d%d", &n, &m, &k)) {
		calcC();
		for (int i=1; i<=m; ++i) { t[i]=0; ap[i]=0; }
		for (int i=1; i<=n; ++i) scanf("%d", &a[i]);
		for (int b=1; b<=n; ++b)  {
			int i=a[b];
			for (int j=1; j*j<=i; ++j)
				if (i/j*j==i)
					if (j*j==i) ++t[j];
					else { ++t[j]; ++t[i/j]; }
		}
		for (int d=1; d<=m; ++d) {
			int tt=t[d], fd=m/d;
			if (tt<n-k) f[d]=0;
			else f[d]=(C[tt]*mpow(fd, n-tt))%MODN*mpow(fd-1, tt+k-n)%MODN;
		}
		for (int i=m; i>=1; --i) {
			/*for (int j=1; j*j<=i; ++j)
				if (i/j*j==i)
					if (j*j==i||j==1) f[j]=(f[j]-f[i]+MODN)%MODN;
					else { f[j]=(f[j]-f[i]+MODN)%MODN; f[i/j]=(f[i/j]-f[i]+MODN)%MODN; }*/
			for (int j=2; j*i<=m; ++j) {
				f[i]=f[i]-f[j*i];
				if (f[i]<0) f[i]+=MODN;
			}
		}
		for (int i=1; i<m; ++i) printf("%d ", (int)f[i]);
		printf("%d\n", (int)f[m]);
	}
	return 0;
}
