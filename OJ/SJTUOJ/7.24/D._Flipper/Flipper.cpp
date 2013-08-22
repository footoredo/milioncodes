#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <string>
#include <vector>

using namespace std;

typedef long long ll;

const int N = 102;
const char msta[2][6] = {"down", "up"};

struct Card {
	int num;
	bool isup;
	Card(int n0, bool i0): num(n0), isup(i0) {}
};

int n, m, ca=0;
char state[N], op[N];
vector<Card> piles[N];

void flip(int p, int nxt) {
	nxt += p;
	for (int i=piles[p].size()-1; i>=0; --i)
		piles[nxt].push_back(Card(piles[p][i].num, !piles[p][i].isup));
}

int main() {
	while (scanf("%d", &n), n) {
		++ca; printf("Pile %d\n", ca);
		for (int i=1; i<=n; ++i)
			piles[i].clear();
		scanf("%s%s", state, op);
		for (int i=1; i<=n; ++i)
			if (state[i-1]=='U')
				piles[i].push_back(Card(i, 1));
			else piles[i].push_back(Card(i, 0));
		int le=1, ri=n;
		for (int i=0; i<n-1; ++i)
			if (op[i]=='R') flip(ri--, -1);
			else flip(le++, 1);
		scanf("%d", &m);
		while (m--) {
			int x; scanf("%d", &x);
			printf("Card %d is a face %s %d.\n",
				x, msta[piles[le][n-x].isup], piles[le][n-x].num);
		}
	}
	return 0;
}
