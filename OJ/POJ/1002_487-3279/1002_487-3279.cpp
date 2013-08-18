#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <map>
#include <algorithm>

using namespace std;

int mapn(char a) {
	switch(a) {
		case '0': return 0;
		case '1': return 1;
		case 'A': case 'B': case 'C': case '2': return 2;
		case 'D': case 'E': case 'F': case '3': return 3;
		case 'G': case 'H': case 'I': case '4': return 4;
		case 'J': case 'K': case 'L': case '5': return 5;
		case 'M': case 'N': case 'O': case '6': return 6;
		case 'P': case 'R': case 'S': case '7': return 7;
		case 'T': case 'U': case 'V': case '8': return 8;
		case 'W': case 'X': case 'Y': case '9': return 9;
	}
}

int numbers[100005];
char s[41];
int hash[10000000];

int main() {
	int n; scanf("%d", &n);
	for (int i=0; i<n; ++i) {
		int t=0;
		scanf("%s", s);
		for (int j=0; s[j]; ++j)
			if (s[j]!='-') t=t*10+mapn(s[j]);
		numbers[i] = t;
		hash[t]++;
	}
	sort(numbers, numbers+n);
	int cnt=0; bool out = false;
	for (int i=0; i<n; ++i) {
		if (!i||i&&numbers[i]-numbers[i-1]) {
            if (hash[numbers[i]]==1) continue;
            out = true;
			for (int j=1000000; j; j/=10) {
				printf("%d", numbers[i]/j%10);
				if (j==10000) printf("-");
			}
			printf(" %d\n", hash[numbers[i]]);
		}
	}
	if (!out) printf("No duplicates.\n");
	//system("pause");
	return 0;
}