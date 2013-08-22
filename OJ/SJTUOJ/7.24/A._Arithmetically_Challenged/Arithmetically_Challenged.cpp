#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <string>

using namespace std;

typedef long long ll;

const int SIZE = 20000007;

int getnum[SIZE];
int num[4], ca=0, cnt;
int op[3], new_num[4], op_order[3], p[4], val[4];
bool used_op[3], used[4];

int mfind(int x) {
	if (p[x]!=x) return p[x]=mfind(p[x]);
	else return x;
}

void unionset(int a, int b, int o) {
	int fa = mfind(a), fb = mfind(b);
	p[fb] = fa;
	switch (o) {
		case 0: val[fa]+=val[fb]; break;
		case 1: val[fa]-=val[fb]; break;
		case 2: val[fa]*=val[fb]; break;
		case 3: val[fa]/=val[fb]; break;
	}
}

void calc() {
	for (int i=0; i<4; ++i) { p[i] = i; val[i] = new_num[i]; }
	for (int i=0; i<3; ++i) {
		int t = op_order[i];
		switch (op[t]) {
			case 0: unionset(t, t+1, 0); break;
			case 1: unionset(t, t+1, 1); break;
			case 2: unionset(t, t+1, 2); break;
			case 3: if (val[mfind(t+1)]==0||val[mfind(t)]%val[mfind(t+1)]!=0)
						return;
					else unionset(t, t+1, 3); break;
		}
	}
	getnum[cnt++] = val[mfind(0)];
}

void search_num(int dep) {
	if (dep==4) calc();
	else
		for (int i=0; i<4; ++i)
			if (!used[i]) {
				new_num[dep] = num[i];
				used[i] = 1;
				search_num(dep+1);
				used[i] = 0;
			}
}

void search_order(int dep) {
	if (dep==3) search_num(0);
	else
		for (int i=0; i<3; ++i)
			if (!used_op[i]) {
				op_order[dep] = i;
				used_op[i] = 1;
				search_order(dep+1);
				used_op[i] = 0;
			}
}

void search(int dep) {
	if (dep==3) {
		search_order(0);
	}
	else for (int i=0; i<4; ++i) {
		op[dep] = i;
		search(dep+1);
	}
}

bool cmp(int a, int b) {
	return a>b;
}

int main() {
	while (scanf("%d%d%d%d", &num[0], &num[1], &num[2], &num[3]), num[0]) {
		++ca; cnt=0;
		memset(used_op, 0, sizeof used_op);
		memset(used, 0, sizeof used);

		search(0);
		sort(getnum, getnum+cnt, cmp);
		int last = 1000000000, len=0, ans=0, anst;
		for (int i=0; i<cnt; ++i) {
			//printf("%d\n", getnum[i]);
			if (!i||(i&&getnum[i]!=getnum[i-1])) {
				if (getnum[i]==last-1) ++len;
				else {
					if (len>ans) {
						ans = len;
						anst = last;
					}
					len = 1;
				}
				last = getnum[i];
			}
		}
		if (len>ans) {
			ans = len;
			anst = last;
		}
		printf("Case %d: %d to %d\n", ca, anst, anst+ans-1);
	}
	return 0;
}
