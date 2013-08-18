#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>

using namespace std;

int main() {
	int n;
	scanf("%d", &n);
	while (n--) {
		int r, e, c;
		scanf("%d%d%d", &r, &e, &c);
		if (e-c>r) printf("advertise\n");
		else if (e-c<r) printf("do not advertise\n");
		else printf("does not matter\n");
	}

	return 0;
}