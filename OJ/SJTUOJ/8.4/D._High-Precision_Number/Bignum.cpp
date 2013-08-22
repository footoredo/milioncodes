#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;

const int LEN = 1003;

typedef long long ll;

struct Bignum {
	int len, bit, pu, sign, p;
	ll dig[LEN];
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
	Bignum repair() {
		while (dig[len]) ++len;
		while (len&&!dig[len-1]) --len;
		if (!len) {
			++len;
			sign=0;
		}
		if (!sign)
			if (len>1||len==1&&dig[0]!=0) sign=1;
		return *this;
	}
	/* assuming all positive */
	bool _greater(Bignum *that) {
		int as=0, bs=0;
		if (this->p>that->p) { bs=this->p-that->p; }
		else { as=-this->p+that->p; }
		Bignum ta(0, this->pu), tb(0, that->pu);
		ta.len=this->len+as; tb.len=that->len+bs;
		for (int i=as; i<ta.len; ++i) ta.dig[i]=this->dig[i-as];
		for (int i=bs; i<tb.len; ++i) tb.dig[i]=that->dig[i-bs];
		if (ta.len>tb.len) return 1;
		else if (tb.len>ta.len) return 0;
		for (int i=ta.len-1; i>=0; --i)
			if (ta.dig[i]>tb.dig[i]) return 1;
			else if (ta.dig[i]>tb.dig[i]) return 0;
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
	Bignum _add(Bignum *that) {
		int as=0, bs=0;
		if (this->p>that->p) { bs=this->p-that->p; }
		else { as=-this->p+that->p; }
		Bignum ta(0, this->pu), tb(0, that->pu);
		ta.len=this->len+as; tb.len=that->len+bs;
		for (int i=as; i<ta.len; ++i) ta.dig[i]=this->dig[i-as];
		for (int i=bs; i<tb.len; ++i) tb.dig[i]=that->dig[i-bs];
		Bignum ret(0, this->pu); ret.len=max(ta.len, tb.len);
		ret.p=ta.p+as;
		int tlen = min(ta.len, tb.len), r=0;
		for (int i=0; i<tlen; ++i) {
			ret.dig[i]+=r+ta.dig[i]+tb.dig[i];
			r=ret.dig[i]/bit;
			ret.dig[i]%=bit;
		}
		if (ta.len<tb.len)
			for (int i=tlen; i<tb.len; ++i) {
				ret.dig[i]+=r+tb.dig[i];
				r=ret.dig[i]/bit;
				ret.dig[i]%=bit;
			}
		else
			for (int i=tlen; i<ta.len; ++i) {
				ret.dig[i]+=r+ta.dig[i];
				r=ret.dig[i]/bit;
				ret.dig[i]%=bit;
			}
		if (r) ret.dig[ret.len++] = r;
		return ret.repair();
	}
	/* assuming all positive and this>that */
	Bignum _minus(Bignum *that) {
		int as=0, bs=0;
		if (this->p>that->p) { bs=this->p-that->p; }
		else { as=-this->p+that->p; }
		Bignum ta(0, this->pu), tb(0, that->pu);
		ta.len=this->len+as; tb.len=that->len+bs;
		for (int i=as; i<ta.len; ++i) ta.dig[i]=this->dig[i-as];
		for (int i=bs; i<tb.len; ++i) tb.dig[i]=that->dig[i-bs];
		Bignum ret(0, this->pu); ret.len=max(ta.len, tb.len);
		ret.p=ta.p+as;
		int tlen = min(ta.len, tb.len), r=0;
		for (int i=0; i<tlen; ++i) {
			ret.dig[i]=ta.dig[i]-tb.dig[i]-r;
			if (ret.dig[i]<0) {
				r=1; ret.dig[i]+=bit;
			}
			else r=0;
		}
		if (ta.len<tb.len)
			for (int i=tlen; i<tb.len; ++i) {
				ret.dig[i]-=r+tb.dig[i];
				if (ret.dig[i]<0) {
					r=1; ret.dig[i]+=bit;
				}
				else r=0;
			}
		else
			for (int i=tlen; i<ta.len; ++i) {
				ret.dig[i]-=r+ta.dig[i];
				if (ret.dig[i]<0) {
					r=1; ret.dig[i]+=bit;
				}
			}
		return ret.repair();
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
	}
	Bignum mpow(int p) {
		if (p==0) return Bignum(1, this->pu);
		if (p==1) return *this;
		Bignum t = this->mpow(p>>1);
		t=t.mult(&t);
		if (p&1) t=t.mult(this);
		return t.repair();
	}
	void display() {
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
		int num[LEN*10];
		for (int i=len-1; i>=0; --i)
			for (int t=bit/10; t; t/=10)
				num[k++]=dig[i]/t%10;
		int l=0, r=k-1;
		while (!num[l]&&l<=r) ++l;
		while ((!num[r]&&l<=r)&&tp) { --r; --tp; }
		for (int i=l; i<=r; ++i) {
			printf("%d", num[i]);
			if (tp&&i+tp==r) printf(".");
		}
		printf("\n");
	}
};

char s[202];

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		int tl;
		Bignum ans(0);
		Bignum t(0);
		while (scanf("%s", s), !((tl=strlen(s))==1&&s[0]=='0')) {
			int st=0, ped=0;
			if (s[0]=='-') {
				st=1;
				t.sign = -1;
			}
			for (int i=st; i+ped<tl; ++i) {
				if (s[i]=='.') {
					t.p = tl-1-i;
					ped=1;
				}
				t.dig[tl-1-i]=s[i+ped]-'0';
			}
			t.len=tl-st-ped;
			t.repair();
			ans=ans.add(&t);
		}
		ans.display();
	}
	return 0;
}
