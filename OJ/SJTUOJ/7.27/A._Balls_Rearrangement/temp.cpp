#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <string>

using namespace std;

typedef long long ll;

const int N = 100005;

int A[N], B[N*3];

int main() {
	int T; scanf("%d", &T);
	int n, a, b;
	scanf("%d%d%d", &n, &a, &b);
	if (a<b) swap(a, b);
	int k=0;
	for (int i=0; i<a; ++i; k=(k+1)%b) {
		A[i]=i; B[i]=k;
	}

	return 0;
}
