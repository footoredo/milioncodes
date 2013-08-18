#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <cstring>
#include <string>

using namespace std;

char websites[500][100], op[100];
int stack[500], top=0, cnt=1;

int main() {
	string nor = "http://www.acm.org/";
	memcpy(websites[1], nor.c_str(), 100);
	//websites[1] = nor.c_str();
	stack[0] = 1; top = 1;
	while (scanf("%s", op), op[0]!='Q') {
		bool ig=0;
		switch (op[0]) {
			case 'V':
				scanf("%s", websites[++cnt]);
				stack[top++]=cnt;
				stack[top]=0;
				break;
			case 'B':
				if (top<=1) ig = 1;
				else --top;
				break;
			case 'F':
				if (!stack[top]) ig = 1;
				else ++top;
				break;
		}
		if (ig) printf("Ignored\n");
		else printf("%s\n", websites[stack[top-1]]);
	}
	return 0;
}