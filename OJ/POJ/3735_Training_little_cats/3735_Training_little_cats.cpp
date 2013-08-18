#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
using namespace std;
typedef long long ll;

struct mat {
	ll arr[105][105];
	int n, m;
	mat(int n=0, int m=0) { init(n, m); }
	void init(int n=0, int m=0) {
		this->n=n; this->m=m;
		memset(arr, 0, sizeof arr);
	}
	mat mult(mat that);
} A, B, Z, m, ret;

mat mat::mult(mat that) {
	ret.init(this->n, that.m);
		for (int i=0; i<=this->n; ++i)
			for (int r=0; r<=this->m; ++r) if (this->arr[i][r])
				for (int k=0; k<=that.m; ++k)
					ret.arr[i][k]+=this->arr[i][r]*that.arr[r][k];
	return ret;
}

mat mpow(mat A, int p) {
	m = Z;
	while (p) {
		if (p&1) m=m.mult(A);
		p>>=1; A=A.mult(A);
	}
	return m;
}

int main() {
	int n, m, k; char ch;
	while (1) {
		scanf("%d%d%d", &n, &m, &k);
		if (!n && !m && !k)break;
		A.init(n, n); B.init(n, 0);
		for (int i=0; i<=n; ++i) A.arr[i][i]=1; B.arr[0][0]=1; Z=A;
		while (k--) {
			getchar(); ch=getchar();
			int op1, op2;
			switch (ch) {
				case 'g': scanf("%d", &op1); ++A.arr[op1][0]; break;
				case 'e': scanf("%d", &op1);
					for (int i=0; i<=n; ++i) A.arr[op1][i]=0;  break;
				case 's': scanf("%d%d", &op1, &op2);
					for (int i=0; i<=n; ++i) swap(A.arr[op1][i], A.arr[op2][i]);  break;
			}
		}
		A=mpow(A, m); B=A.mult(B);
		for (int i=1; i<=n; ++i) printf("%lld ", B.arr[i][0]); printf("\n");
	}
	return 0;
}