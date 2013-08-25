#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>

using namespace std;

#define REP(i,n) for(int i=0; i<n; ++i)
typedef long long ll;
const string FILENAME = "fib_matrix";
const int MODN = 2012182013, N = 1000006;

inline void setIO() {
	freopen("input", "r", stdin);
	freopen((FILENAME+".myout").c_str(), "w", stdout);
}

struct Mat {
	int n, m;
	ll mat[5][5];
	Mat(int n=3, int m=3): n(n), m(m) { REP(i,n) REP(j,m) mat[i][j]=0; }
	inline Mat mult(Mat *an);
	Mat pow(int l, char *num);
} one, tmp, tp[10], rec, c[2], cn, ans(3, 1);

inline Mat Mat::mult(Mat *an) {
	tmp=Mat(an->n,m);
	REP(i,an->n) REP(j,m) { REP(k,n)
		tmp.mat[i][j]+=mat[k][j]*an->mat[i][k];
		tmp.mat[i][j]%=MODN;
	}
/*if (m>1) {
	printf("[ ");
	REP(i,3) printf("%lld ",mat[0][i]);
	printf("]   [ ");
	REP(i,3) printf("%lld ",an->mat[0][i]);
	printf("]   [ ");
	REP(i,3) printf("%lld ",tmp.mat[0][i]);
	printf("]\n[ ");
	REP(i,3) printf("%lld ",mat[1][i]);
	printf("] * [ ");
	REP(i,3) printf("%lld ",an->mat[1][i]);
	printf("] = [ ");
	REP(i,3) printf("%lld ",tmp.mat[1][i]);
	printf("]\n[ ");
	REP(i,3) printf("%lld ",mat[2][i]);
	printf("]   [ ");
	REP(i,3) printf("%lld ",an->mat[2][i]);
	printf("]   [ ");
	REP(i,3) printf("%lld ",tmp.mat[2][i]);
	printf("]\n\n");
}*/
	return tmp;
}

Mat Mat::pow(int l, char *num) {
/*cout<<"Begin pow().. ";
printf("l=%d, num=", l);
REP(i,l) putchar(num[i]+'0');
putchar('\n');*/
	tp[0]=one; REP(i,9) tp[i+1]=tp[i].mult(this);
	cn=one;
	REP(i,l) {
//printf("  i=%d, num[i]=%d\n", i, num[i]);
		rec=cn=cn.mult(&cn);
		REP(j,2) rec=rec.mult(&rec);
		cn=rec.mult(&cn);
		cn=cn.mult(tp+num[i]);
	}
/*cout<<"End pow.. ";
printf("l=%d, num=", l);
REP(i,l) putchar(num[i]+'0');
putchar('\n');*/
	return cn;
}

void m1(int l, char *num) { --num[l-1];
	for (int i=l-1, r=0; i>=0; --i) {
		num[i]-=r; if (num[i]<0) { num[i]+=10; r=1; } else r=0;
	}
}

int l[8];
char n[8][N], ch;
ll m[6];

int main() {
	setIO();
	REP(i,3) one.mat[i][i]=1;
	REP(i,8) while ((ch=getchar())!=' '&&(ch!=10&&ch!=13)) n[i][l[i]++]=ch-'0';
//REP(i,8) { printf("%d\n", l[i]); }
//REP(i,8) { printf("%s\n", n[i]); }
	//REP(i,8) REP(j,l[i])  n[i][j]-='0';
	REP(i,6) REP(j,l[i+2]) m[i]=(m[i]*10+n[i+2][j])%MODN;
//REP(i,6) printf("%lld\n", m[i]);
	REP(i,2) {
		c[i].mat[0][0]=1; c[i].mat[1][2]=1;
		c[i].mat[2][0]=m[2+i*3]; c[i].mat[2][1]=m[i*3];
		c[i].mat[2][2]=m[1+i*3];
	} m1(l[0],n[0]); m1(l[1],n[1]); m1(l[1],n[1]);
/*REP(i,2) REP(j,3) {
	REP(k,3) printf("%lld ",c[i].mat[j][k]);
	putchar('\n');
}*/
//REP(i,2) { REP(j,l[i]) putchar(n[i][j]+'0'); putchar('\n'); }
	c[1]=c[1].mult(c+1); c[0]=c[0].pow(l[1],n[1]);
	cn=c[0].mult(c+1).pow(l[0],n[0]).mult(c);
	REP(i,3) ans.mat[i][0]=1; ans=ans.mult(&cn);
	cout<<ans.mat[2][0]<<endl;
	return 0;
}
