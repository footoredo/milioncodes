#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

const int N = 10004, LEN = 21;

struct Data {
	char en[LEN];
	int order;
} words[N];

bool cmp1(Data a, Data b) {
	return strcmp(a.en, b.en)>0;
}

bool cmp2(int a, int b) {
	return words[a].order<words[b].order;
}

int n, t, Q[N];
bool chosen[N];
char buffer[LEN], ch, changed[LEN];

int b_find(char *ts) {
	int l=0, r=n-1, t;
	while (l<=r) {
		int mid = (l+r)/2;
		if (!(t=strcmp(ts, words[mid].en))) return mid;
		else if (t>0) r = mid-1;
		else l = mid+1;
	}
	return -1;
}

int main() {
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
	while (scanf("%s", words[n].en), words[n].en[0]!='#') {
		words[n].order = n++;
	}
	sort(words, words+n, cmp1);
	while (scanf("%s", buffer), buffer[0]!='#') {
		if (b_find(buffer)+1) {
			printf("%s is correct\n", buffer);
			continue;
		}
		memset(chosen, 0, sizeof(chosen));
		int len = 0;
		Q[len] = -1;
		if (buffer[1]) {
			for (int i=0; i<strlen(buffer); ++i) {
				int k=0, t;
				for (int j=0; j<strlen(buffer); ++j)
					if (j!=i) changed[k++] = buffer[j];
				changed[k] = 0;
				if ((t=b_find(changed))+1&&!chosen[t]) {
					Q[len++] = t;
					chosen[t] = 1;
				}
			}
		}
		memcpy(changed, buffer, strlen(buffer)+1);
		for (int i=0; i<strlen(buffer); ++i)
			for (char c='a'; c<='z'; ++c)
				if (c!=buffer[i]) {
					int t;
					changed[i] = c;
					if ((t=b_find(changed))+1&&!chosen[t]) {
						Q[len++] = t;
						chosen[t] = 1;
					}
					changed[i] = buffer[i];
				}
		for (int i=0; i<=strlen(buffer); ++i)
			for (char c='a'; c<='z'; ++c) {
				int k=0, t;
				for (int j=0; j<=strlen(buffer); ++j) {
					if (j==i) changed[k++] = c;
					changed[k++] = buffer[j];
				}
				if ((t=b_find(changed))+1&&!chosen[t]) {
					Q[len++] = t;
					chosen[t] = 1;
				}
			}
		printf("%s:", buffer);
		sort(Q, Q+len, cmp2);
		for (int i=0; i<len; ++i)
			if (!i||i&&Q[i]!=Q[i-1]) printf(" %s", words[Q[i]].en);
		printf("\n");
	}
	return 0;
}
