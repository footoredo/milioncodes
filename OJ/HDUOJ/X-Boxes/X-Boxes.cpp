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

const int LEN = 3003;
inline int mmax(int a, int b) { 
	return a<b?b:a;
}
inline int mmin(int a, int b) { 
	return a>b?b:a;
}

ll r;

struct Bignum {
	int len, pu, sign, p;
	ll dig[LEN], bit;
	Bignum(ll n=0, int push=1) {
		memset(dig, 0, sizeof dig);
		if (n>0) sign=1;
		else if (n==0) sign=0;
		else { sign=-1; n/=-1; }
		bit = 1;
		for (int i=1; i<=push; ++i, bit*=10);
		for (len=0; n; dig[len++]=n%bit, n/=bit);
		if (!len) ++len;
		p=0; pu=push;
	}
	void repair() {
		while (dig[len]) ++len;
		while (len&&!dig[len-1]) --len;
		if (!len) {
			++len;
			sign=0;
		}
		if (!sign&&(len>1||len==1&&dig[0])) sign=1;
		//return *this;
	}
	/* assuming all positive */
	bool _greater(Bignum *that) {
		if (this->len>that->len) return 1;
		else if (that->len>this->len) return 0;
		for (int i=this->len-1; i>=0; --i)
			if (this->dig[i]>that->dig[i]) return 1;
			else if (that->dig[i]>this->dig[i]) return 0;
		return 0;
	}
	bool greater(Bignum *that) {
		if (this->sign==1)
			if (that->sign==1) return this->_greater(that);
			else return 1;
		else if (that->sign==1) return 0;
		else return that->_greater(this);
	}
	/* assuming all positive */
	inline void __add(Bignum *that) {
		ll r=0; //len=mmax(len, that->len);
		if (that->len>len) len=that->len;
		for (int i=0; i<len; ++i) {
			dig[i]+=r+that->dig[i];
			r=dig[i]/bit;
			if (dig[i]>bit) dig[i]-=bit;
		}
		repair();
	}
	Bignum _add(Bignum *that) {
		int tlen = mmin(that->len, this->len); ll r=0;
		Bignum ret(0, this->pu); ret.len=mmax(that->len, this->len);
		//REP(i, tlen+2) ret.dig[i]=0;
		for (int i=0; i<tlen; ++i) {
			ret.dig[i]+=r+this->dig[i]+that->dig[i];
			r=ret.dig[i]/bit;
			if (ret.dig[i]>bit) ret.dig[i]-=bit;
		}
		if (this->len<that->len)
			for (int i=tlen; i<that->len; ++i) {
				ret.dig[i]+=r+that->dig[i];
				r=ret.dig[i]/bit;
				if (ret.dig[i]>bit) ret.dig[i]-=bit;
			}
		else
			for (int i=tlen; i<this->len; ++i) {
				ret.dig[i]+=r+this->dig[i];
				r=ret.dig[i]/bit;
				if (ret.dig[i]>bit) ret.dig[i]-=bit;
			}
		if (r) ret.dig[ret.len++] = r;
		return ret.repair(), ret;
	}
	/* assuming all positive and this>that */
	/*Bignum _minus(Bignum *that) {
		Bignum ret(0, this->pu); ret.len=max(that->len, this->len);
		int tlen = min(that->len, this->len), r=0;
		for (int i=0; i<tlen; ++i) {
			ret.dig[i]=this->dig[i]-that->dig[i]-r;
			if (ret.dig[i]<0) {
				r=1; ret.dig[i]+=bit;
			}
			else r=0;
		}
		if (this->len<that->len)
			for (int i=tlen; i<that->len; ++i) {
				ret.dig[i]-=r+that->dig[i];
				if (ret.dig[i]<0) {
					r=1; ret.dig[i]+=bit;
				}
				else r=0;
			}
		else
			for (int i=tlen; i<this->len; ++i) {
				ret.dig[i]-=r+this->dig[i];
				if (ret.dig[i]<0) {
					r=1; ret.dig[i]+=bit;
				}
			}
		return ret.repair(), ret;
	}
	Bignum add(Bignum *that) {
		Bignum ret;
		if (this->sign==0) return that->repair();
		if (that->sign==0) return this->repair();
		if (this->sign==1)
			if (that->sign==1)
				return this->_add(that);
			else
				if (!that->_greater(this))
					return this->_minus(that);
				else {
					ret = that->_minus(this);
					ret.sign *= -1;
					return ret.repair();
				}
		else
			if (that->sign==1)
				if (!that->_greater(this)) {
					ret = this->_minus(that);
					ret.sign *= -1;
					return ret.repair();
				}
				else return that->_minus(this);
			else {
				ret = this->_add(that);
				ret.sign *= -1;
				return ret.repair();
			}
	}
	Bignum minus(Bignum *that) {
		that->sign *= -1;
		Bignum ret = this->add(that);
		that->sign *= -1;
		return ret;
	}
	Bignum mult(Bignum *that) {
		Bignum ret(0, this->pu); ret.len=this->len+that->len-1;
		ret.sign = this->sign * that->sign;
		ret.p=this->p+that->p;
		for (int i=0; i<this->len; ++i)
			for (int j=0; j<that->len; ++j) {
				ret.dig[i+j]+=this->dig[i]*that->dig[j];
				ret.dig[i+j+1]+=ret.dig[i+j]/bit;
				ret.dig[i+j]%=bit;
			}
		for (int i=0; i<ret.len; ++i) {
			ret.dig[i+1]+=ret.dig[i]/bit;
			ret.dig[i]%=bit;
		}
		return ret.repair();
	}*/
	void div(ll t) {
		//Bignum ret(0, this->pu); ret.len=len;
		//REP(i, len+2) ret.dig[i]=0;
		r=0;
		for (int i=len-1; i>=0; --i) {
			r=r*bit+dig[i];
			dig[i]=r>>t; r=r&(1<<t);
		}
		repair();
	}
	/*Bignum mpow(int p) {
		if (p==0) return Bignum(1, this->pu);
		if (p==1) return *this;
		Bignum t = this->mpow(p>>1);
		t=t.mult(&t);
		if (p&1) t=t.mult(this);
		return t.repair();
	}*/
	/*void display() {
		if (sign==-1) printf("-");
		if (!sign) {
			printf("0\n");
			return;
		}
		if (p>=len*pu) {
			printf(".");
			for (int i=p; i>len*pu; --i) printf("0");
		}
		int k = 0, tp=p;
		ll num[LEN*20];
		for (int i=len-1; i>=0; --i)
			for (int t=bit/10; t; t/=10)
				num[k++]=dig[i]/t%10;
		int l=0, r=k-1;
		while (!num[l]&&l<=r) ++l;
		while ((!num[r]&&l<=r)&&tp) { --r; --tp; }
		for (int i=l; i<=r; ++i) {
			printf("%lld", num[i]);
			if (tp&&i+tp==r) printf(".");
		}
		printf("\n");
	}*/
};

inline int lowbit(int x) { return x&(-x); }
inline int mgcd(int x, int y) { return y?mgcd(y, x%y):x; }

int T;
Bignum ans, t, one(1, 18), ta;
char tn[10004];

int main() {
	//freopen("X-Boxes.in", "r", stdin);
	//freopen("X-Boxes.out", "w", stdout);
	scanf("%d", &T);
	ans=Bignum(0, 18); t=Bignum(0, 18);
	while (T--) {
		ans.len=t.len=1;
		ans.sign=t.sign=0;
		//memset(ans.dig, 0, sizeof ans.dig);
		//memset(t.dig, 0, sizeof t.dig);
		ans.dig[0]=ans.dig[1]=ans.dig[2]=0;
		t.dig[0]=t.dig[1]=t.dig[2]=0;
		int k, tlen=-1; char tc=getchar();
		while ((tc=getchar())!=' ') tn[++tlen]=tc; ++tlen;
		scanf("%d", &k); 
		t.len=tlen/18+(tlen%18>0);
		REP(i, t.len) {
			ll tt=0, b=1; int tp=tlen-i*18-1;
			for (int j=0; j<=tp&&j<18; ++j) { tt+=(tn[tp-j]-'0')*b; b*=10; }
			t.dig[i] = tt;
		} t.repair();
		t.div(k-1);
		ll ones=0, bit=t.bit; r=0;
		if (t.dig[0]&1) ++ones;
		ans=ans._add(&t);
		while (t.sign) {
			t.div(k); //t.display();
			if (t.dig[0]&1) ++ones;
			r=0; //len=mmax(len, that->len);
			if (t.len>ans.len) ans.len=t.len;
			for (int i=0; i<ans.len; ++i) {
				ans.dig[i]+=r+t.dig[i];
				r=ans.dig[i]/bit;
				if (ans.dig[i]>bit) ans.dig[i]-=bit;
			}
			ans.repair();
			//ans.__add(&t);
			//ta.display();
		} one=Bignum(ones, 18);
		ans=ans._add(&one);
		ans.div(1);
		for (int i=ans.len-1; i>=0; --i) {
			ll b=1;
			if (i==ans.len-1) printf("%lld", ans.dig[i]);
			else {
				int j;
				for (j=0, b=1; b<=ans.dig[i]; b*=10, ++j);
				if (!j) ++j;
				REP(k, 18-j) printf("0");
				printf("%lld", ans.dig[i]);
			}
		}
		printf("\n");
	}
	return 0;
}
