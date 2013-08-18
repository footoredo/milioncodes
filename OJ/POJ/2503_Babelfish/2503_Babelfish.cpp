#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 100005, LEN = 21;

struct Data {
	char en[LEN], fr[LEN];
} words[N];

bool cmp(Data a, Data b) {
	return strcmp(a.fr, b.fr)>0;
}

int n, t;
char ts[LEN], ch;

int bfind() {
	int l=0, r=n-1, t;
	while (l<=r) {
		int mid = (l+r)/2;
		if (!(t=strcmp(ts, words[mid].fr))) return mid;
		else if (t>0) r = mid-1;
		else l = mid+1;
	}
	return -1;
}

int main() {
		while (gets(ts)!=NULL&&ts[0]!='\0') {
			sscanf(ts, "%s %s", words[n].en, words[n].fr);
			++n;
		}
		sort(words, words+n, cmp);
		while (gets(ts)!=NULL) {
			if ((t=bfind())+1) printf("%s\n", words[t].en);
			else printf("eh\n");
		}
	return 0;
}
