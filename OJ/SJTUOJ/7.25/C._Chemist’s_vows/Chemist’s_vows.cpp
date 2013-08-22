#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <string>

using namespace std;

const char table[114][3] = {
"H", "He",
"Li", "Be", "B", "C", "N", "O", "F", "Ne",
"Na","Mg","Al","Si","P","S","Cl","Ar",
"K","Ca","Sc","Ti","V","Cr","Mn","Fe","Co","Ni",
"Cu","Zn","Ga","Ge","As","Se","Br","Kr",
"Rb","Sr","Y","Zr","Nb","Mo","Tc","Ru",
"Rh","Pd","Ag","Cd","In","Sn","Sb","Te","I","Xe",
"Cs","Ba","Hf","Ta","W","Re","Os","Ir","Pt","Au",
"Hg","Tl","Pb","Bi","Po","At","Rn",
"Fr","Ra","Rf","Db","Sg","Bh","Hs","Mt","Ds","Rg","Cn","Fl","Lv",
"La","Ce","Pr","Nd","Pm","Sm","Eu","Gd","Tb","Dy","Ho" ,
"Er","Tm","Yb","Lu",
"Ac","Th","Pa","U","Np","Pu","Am","Cm","Bk","Cf","Es","Fm","Md",
"No","Lr"
};

typedef long long ll;

const int N = 50004;

char word[N];
bool f[N];

inline char lower(char a) {
	return a-'A'+'a';
}

int main() {
	int n; scanf("%d", &n);
	while (n--) {
	scanf("%s", word+1);
	memset(f, 0, sizeof f);
	f[0] = 1;
	int len = strlen(word+1);
	for (int i=1; i<=len; ++i) {
		for (int j=0; !f[i]&&j<114; ++j)
			if (strlen(table[j])==1)
				if (lower(table[j][0])==word[i])
					f[i] = f[i]||f[i-1];
				else;
			else if (i>1&&(table[j][1]==word[i]&&
					lower(table[j][0])==word[i-1]))
					f[i] = f[i]||f[i-2];
	}
	if (f[len]) printf("YES\n");
	else printf("NO\n");
}
	return 0;
}
