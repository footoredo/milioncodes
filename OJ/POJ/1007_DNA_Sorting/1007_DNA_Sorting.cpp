#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 102, M = 102;

struct Data {
	char s[N];
	int num;
} seq[M];

bool cmp(Data a, Data b) {
	return a.num<b.num;
}

int n, m;

void solve(int k) {
	int sum=0;
	for (int i=1; i<n; ++i)
		for (int j=0; j<i; ++j)
			if (seq[k].s[j]>seq[k].s[i]) ++sum;
	seq[k].num = sum;
}

int main() {
	scanf("%d%d", &n, &m);
	for (int i=0; i<m; ++i) {
		scanf("%s", seq[i].s);
		solve(i);
	}
	sort(seq, seq+m, cmp);
	for (int i=0; i<m; ++i)
		printf("%s\n", seq[i].s);
	return 0;
}
