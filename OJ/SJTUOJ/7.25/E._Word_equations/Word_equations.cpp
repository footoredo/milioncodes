#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <string>
#include <map>

using namespace std;

typedef long long ll;

const int N = 2003;

struct Val {
	char sy[10];
	bool type;
	int wordn, mn1, mn2;
} vals[N];
/*
struct Node {
	int valn;
	char cur;
	int son[26];
} mem[N];
*/
char tmp[5000], eq[5], pl[5], words[N][15];
int tcnt, vcnt=0, root;
string fword;
map<string, int> mhash;
/*
int appear(int x, char *s) {
	if (!x) {
		x=tcnt++;
		mem[x].cur=s[0];
		mem[x].valn=-1;
	}
	if (s[1]) {
		mem[x].son[s[1]-'A']=appear(mem[x].son[s[1]-'A'],s+1);
	}
	else
		if (mem[x].valn==-1) {
			mem[x].valn=vcnt;
			memcpy(vals[vcnt++].sy, tmp, sizeof tmp);
		}
}

int mfind(int x, char *s) {
	if (!x) return -1;
	if (s[1])
		return mfind(mem[x].son[s[1]-'A'],s+1);
	else
		return mem[x].valn==-1;
}
*/
string solve(int x) {
	if (vals[x].type==0) return string(words[vals[x].wordn]);
	return solve(vals[x].mn1)+solve(vals[x].mn2);
}

string f[N];
int uplist[N];
bool fin[N], led[N], red[N];

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		int n, wcnt=0, l=0, r=0; scanf("%d", &n);
		vcnt=0;
		mhash = map<string, int>();
		root=1; tcnt=2;
		memset(fin, 0, sizeof fin);
		memset(led, 0, sizeof led);
		memset(red, 0, sizeof red);
		while (n--) {
			scanf("%s%s", tmp, eq);
			//mem[root].son[tmp[0]-'A']=appear(mem[root].son[tmp[0]-'A'], tmp);
			int k;
			if (!(k=mhash[string(tmp)])) k=mhash[string(tmp)]=vcnt++;
			f[k] = "";
			scanf("%s", tmp);
			if (tmp[0]>='A'&&tmp[0]<='Z') {
				int tk;
				if (!(tk=mhash[string(tmp)])) tk=mhash[string(tmp)]=vcnt++;
				vals[k].type = 1;
				vals[k].mn1 = tk;
				scanf("%s%s", pl, tmp);
				if (!(tk=mhash[string(tmp)])) tk=mhash[string(tmp)]=vcnt++;
				vals[k].mn2 = tk;
			}
			else {
				vals[k].type = 0;
				vals[k].wordn = wcnt;
				f[k] = string(tmp);
				fin[k] = 1;
				uplist[r++] = k;
				//memcpy(words[wcnt++], tmp, sizeof tmp);
			}
		}
		scanf("%s", tmp);
		//fword = solve(mhash[string(tmp)]);
		while (l<r) {
			int t = uplist[l++];
			for (int i=0; i<vcnt; ++i)
				if (!fin[i]) {
					if (t==vals[i].mn1&&!led[i]) {
						f[i]=f[t]+f[i];
						led[i]=1;
					}
					if (t==vals[i].mn2&&!red[i]) {
						f[i]=f[i]+f[t];
						red[i]=1;
					}
					if (led[i]&&red[i]) {
						fin[i]=1;
						uplist[r++]=i;
					}
				}
		}
		fword = f[mhash[string(tmp)]];
		//cout<<fword<<endl;
		scanf("%s", tmp);
		int len = strlen(tmp), last=-1, flen = fword.length();
		bool noed = 0;
		for (int i=0; i<len; ++i) {
			bool flag = 0;
			for (int j=last+1; j<flen; ++j)
				if (fword[j]==tmp[i]) {
					last = j;
					flag = 1;
					break;
				}
			if (!flag) {
				noed = 1;
				printf("NO\n");
				break;
			}
		}
		if (!noed) printf("YES\n");
	}
	return 0;
}
