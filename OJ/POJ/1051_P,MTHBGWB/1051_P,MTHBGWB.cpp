#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>

using namespace std;

string morse(char a) {
	switch (a) {
		case 'A':return ".-";
		case 'H':return "....";
		case 'O':return "---";
		case 'V':return "...-";
		case 'B':return "-...";
		case 'I':return "..";
		case 'P':return ".--.";
		case 'W':return ".--";
		case 'C':return "-.-.";
		case 'J':return ".---";
		case 'Q':return "--.-";
		case 'X':return "-..-";
		case 'D':return "-..";
		case 'K':return "-.-";
		case 'R':return ".-.";
		case 'Y':return "-.--";
		case 'E':return ".";
		case 'L':return ".-..";
		case 'S':return "...";
		case 'Z':return "--..";
		case 'F':return "..-.";
		case 'M':return "--";
		case 'T':return "-";
		case 'G':return "--.";
		case 'N':return "-.";
		case 'U':return "..-";
		case '_':return "..--";
		case '.':return "---.";
		case ',':return ".-.-";
		case '?':return "----";
	}
}

char letter(char *s) {
	for (char i='A'; i<='Z'; ++i)
		if (!strcmp(s, morse(i).c_str())) return i;
	if (!strcmp(s, morse('_').c_str())) return '_';
	if (!strcmp(s, morse('.').c_str())) return '.';
	if (!strcmp(s, morse('?').c_str())) return '?';
	if (!strcmp(s, morse(',').c_str())) return ',';
}

int lens[1003], cnt=0, m;
char mo[1003], se[202];

int main() {
	int n; scanf("%d", &n);
	for (int i=1; i<=n; ++i) {
		cnt=m=0; scanf("%s", se);
		//printf("%s\n", se);
		for (int j=0; j<strlen(se); ++j) {
			char tmp[10];
			strcpy(tmp, morse(se[j]).c_str());
			//printf("%c %s\n", se[j], tmp);
			lens[cnt++] = strlen(tmp);
			for (int k=0; k<strlen(tmp); ++k, ++m)
				mo[m] = tmp[k];
		}
		mo[m]=0;
		printf("%d: ", i);
		int p=0;
		for (int j=cnt-1; j>=0; --j) {
			char tmp[10];
			strncpy(tmp, mo+p, lens[j]);
			tmp[lens[j]]=0;
			//printf("\t%d %s\n", lens[j], tmp);
			p+=lens[j];
			printf("%c", letter(tmp));
		}
		printf("\n");
	}
	return 0;
}
