#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>

using namespace std;

int a[10004];

int main() {
	int n; scanf("%d", &n);
	for (int i=0; i<n; ++i) scanf("%d", &a[i]);
	sort(a, a+n);
	printf("%d\n", a[n/2]);
	return 0;
}