#include <stdio.h>
#include <string.h>
const int mod = 2012182013;
struct Matrix
{
	long long a1, a2, a3, a4, a5, a6;
	Matrix()
	{
		a1 = a2 = a3 = a4 = a5 = a6 = 0;
	}
	Matrix(const Matrix &x)
	{
		a1 = x.a1, a2 = x.a2, a3 = x.a3, a4 = x.a4, a5 = x.a5, a6 = x.a6;
	}
	void operator *= (const Matrix &x)
	{
		long long b1 = (a1 * x.a1 + a2 * x.a3) % mod;
		long long b2 = (a1 * x.a2 + a2 * x.a4) % mod;
		long long b3 = (a3 * x.a1 + a4 * x.a3) % mod;
		long long b4 = (a3 * x.a2 + a4 * x.a4) % mod;
		long long b5 = (a5 * x.a1 + a6 * x.a3 + x.a5) % mod;
		long long b6 = (a5 * x.a2 + a6 * x.a4 + x.a6) % mod;
		a1 = b1, a2 = b2, a3 = b3, a4 = b4, a5 = b5, a6 = b6;
	}
};
int a, b, c, d, e, f, nl, ml;
char n[1000002], m[1000002], na[1000002], nb[1000002], nc[1000002], nd[1000002], ne[1000002], nf[1000002];
Matrix mata, matb;
int Mod(char *num)
{
	int l = strlen(num);
	long long cur = 0;
	for(int i = 0; i < l; cur = cur * 10 + (num[i++] - '0'))
		cur %= mod;
	return cur % mod;
}
Matrix MatPow(Matrix mat, char *num, int l)
{
	Matrix ret;
	ret.a1 = ret.a4 = 1;
	for(int i = l - 1; i >= 0; i--)
	{
		Matrix mat1 = mat, mat2 = mat;
		mat2 *= mat2;
		Matrix mat3 = mat2;
		mat3 *= mat3;
		Matrix mat4 = mat3;
		mat4 *= mat4;
		if(num[i] & 1)
			ret *= mat1;
		num[i] >>= 1;
		if(num[i] & 1)
			ret *= mat2;
		num[i] >>= 1;
		if(num[i] & 1)
			ret *= mat3;
		num[i] >>= 1;
		if(num[i] & 1)
			ret *= mat4;
		mat *= mat1;
		mat *= mat4;
	}
	return ret;
}
int main()
{
	scanf("%s%s%s%s%s%s%s%s", n, m, na, nb, nc, nd, ne, nf);
	nl = strlen(n), ml = strlen(m);
	a = Mod(na), b = Mod(nb), c = Mod(nc), d = Mod(nd), e = Mod(ne), f = Mod(nf);
	mata.a3 = matb.a3 = 1;
	mata.a2 = a, mata.a4 = b, mata.a6 = c;
	matb.a2 = d, matb.a4 = e, matb.a6 = f;
	for(int i = 0; i < nl; i++)
		n[i] -= '0';
	for(int i = 0; i < ml; i++)
		m[i] -= '0';
	n[nl - 1]--;
	for(int i = nl - 1; i >= 0 && n[i] < 0; i--)
		n[i] += 10, n[i - 1]--;
	m[ml - 1] -= 2;
	for(int i = ml - 1; i >= 0 && m[i] < 0; i--)
		m[i] += 10, m[i - 1]--;
	Matrix tmp = MatPow(mata, m, ml);
	Matrix sub = tmp;
	sub *= matb, sub *= matb;
	Matrix ans = MatPow(sub, n, nl);
	ans *= tmp;
	printf("%d", (int)((ans.a2 + ans.a4 + ans.a6) % mod));
	return 0;
}
