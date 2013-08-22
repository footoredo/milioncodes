#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;

const int LEN = 100005;

typedef long long ll;

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
	Bignum repair() {
		while (dig[len]) ++len;
		while (len&&!dig[len-1]) --len;
		if (!len) {
			++len;
			sign=0;
		}
		return *this;
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
	Bignum _add(Bignum *that) {
		int tlen = min(that->len, this->len), r=0;
		Bignum ret(0, this->pu); ret.len=max(that->len, this->len);
		for (int i=0; i<tlen; ++i) {
			ret.dig[i]+=r+this->dig[i]+that->dig[i];
			r=ret.dig[i]/bit;
			ret.dig[i]%=bit;
		}
		if (this->len<that->len)
			for (int i=tlen; i<that->len; ++i) {
				ret.dig[i]+=r+that->dig[i];
				r=ret.dig[i]/bit;
				ret.dig[i]%=bit;
			}
		else
			for (int i=tlen; i<this->len; ++i) {
				ret.dig[i]+=r+this->dig[i];
				r=ret.dig[i]/bit;
				ret.dig[i]%=bit;
			}
		if (r) ret.dig[ret.len++] = r;
		return ret.repair();
	}
	int add1() {
		this->dig[0]+=1;
		int ret=0;
		int r=this->dig[0]/bit;
		this->dig[0]%=bit;
		int p=1;
		while (r&&p<len) {
			ret=p;
			this->dig[p]+=r;
			r=this->dig[p]/bit;
			this->dig[p++]%=bit;
		}
		if (r) {
			this->dig[this->len++] = r;
			ret=len-1;
		}
		this->repair();
		return ret;
	}
	/* assuming all positive and this>that */
	Bignum _minus(Bignum *that) {
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
} bn;

char snum[100005];

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%s", snum);
		bn=Bignum(1);
		bn.len=strlen(snum);
		for (int i=0; i<bn.len; ++i)
			bn.dig[bn.len-1-i]=snum[i]-'0';
		while (1) {
			int r=bn.add1(), tsum=0;
			for (int i=0; i<bn.len; ++i)
				tsum+=bn.dig[i];
			if (tsum/10*10==tsum) break;
		}
		for (int i=bn.len-1; i>=0; --i)
			printf("%d", bn.dig[i]);
		printf("\n");
	}
	return 0;
}
