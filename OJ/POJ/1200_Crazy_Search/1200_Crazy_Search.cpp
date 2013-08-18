#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <map>

using namespace std;

const int SIZE = 16000007;
/*
struct Trie {
	bool word_here;
	int sons[26];
} mem[SIZE];

int size = 1, ans = 0, root = 0;

int ins(int x, int len, char *s) {
	if (x==0) x = size++;
	if (!len) {
		ans += !mem[x].word_here;
		mem[x].word_here = 1;
	}
	else mem[x].sons[s[0]-'a'] = ins(mem[x].sons[s[0]-'a'], len-1, s+1);
	return x;
}*/

bool hash[SIZE], appear[128];
int po[128], n, nc, ans=0;
char str[SIZE];

int solve(char *s) {
	int ret = 0;
	for (int i=0; i<n; ++i)
		ret=ret*nc+po[s[i]];
	return ret;
}

int main() {
	scanf("%d%d", &n, &nc);
	scanf("%s", str);
	int len = strlen(str);
	for (int i=0; i<len; ++i) appear[str[i]] = 1;
	int k=0;
	for (int i=0; i<128; ++i) if (appear[i]) po[i] = k++;
	
	for (int i=0; i+n<=len; ++i) {
		int t = solve(str+i);
		if (!hash[t]) {
			++ans;
			hash[t] = 1;
		}
	}
	
	printf("%d\n", ans);
	return 0;
}
