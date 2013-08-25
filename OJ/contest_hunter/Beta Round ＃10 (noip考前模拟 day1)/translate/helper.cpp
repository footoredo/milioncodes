#include <cstdio>
#include <cstring>
#include <cstdlib>
const int test = 20;
const char File[] = "translate.cpp";
int word[26];
char ch[2][1000], in[1000], out[1000];
FILE *fin, *fout, *fstd;
void start() { fprintf(fstd, "#include <cstdio>\nstruct Node { int trans[26]; } word;\nint n;\nchar ch[1000000];\nint main() {\n\tscanf(\"%cd\", &n);\n\tswitch(n) {\n", '%'); }
void Nothing(int x) { fprintf(fstd, "\t\tcase %2d: break;\n", x); }
void Case(int x)
{
	fprintf(fstd, "\t\tcase %2d: word = (Node){", x);
	for(int i = 0; i < 25; ++i) fprintf(fstd, "%d, ", word[i]);
	fprintf(fstd, "%d}; break;\n", word[25]);
}
void end() { fprintf(fstd, "\t}\n\twhile(gets(ch)) {\n\t\tfor(int i = 0; ch[i]; ++i)\n\t\t\tif('a' <= ch[i] && ch[i] <= 'z') ch[i] = word.trans[(int)ch[i] - 'a'] + 'a';\n\t\t\telse if('A' <= ch[i] && ch[i] <= 'Z') ch[i] = word.trans[(int)ch[i] - 'A'] + 'A';\n\t\tputs(ch);\n\t}\n}\n"); }
bool translate()
{
	memset(word, 0, sizeof word);
	while(1)
	{
		bool flag1 = fscanf(fin, "%s", ch[0]) != EOF, flag2 = fscanf(fout, "%s", ch[1]) != EOF;
		if(flag1 ^ flag2) return false;
		else if(!(flag1 | flag2)) return true;
		for(int i = 0; ch[0][i] || ch[1][i]; ++i)
			if(!(ch[0][i] && ch[1][i])) return false;
			else if('a' <= ch[0][i] && ch[0][i] <= 'z')
			{
				if('A' <= ch[1][i] && ch[1][i] <= 'Z') return false;
				if(!word[(int)ch[0][i] - 'a']) word[(int)ch[0][i] - 'a'] = ch[1][i] - 'a';
				else if(word[(int)ch[0][i] - 'a'] != ch[1][i] - 'a') return false;
			}
			else if('A' <= ch[0][i] && ch[0][i] <= 'Z')
			{
				if('a' <= ch[1][i] && ch[1][i] <= 'z') return false;
				if(!word[(int)ch[0][i] - 'A']) word[(int)ch[0][i] - 'A'] = ch[1][i] - 'A';
				else if(word[(int)ch[0][i] - 'A'] != ch[1][i] - 'A') return false;
			}
	}
}
int main()
{
	fstd = fopen(File, "w");
	start();
	for(int i = 1; i <= test; ++i)
	{
		printf("Case %2d:\n", i);
		scanf("%s%s", in, out);
		if((fin = fopen(in, "r")) == NULL || (fout = fopen(out, "r")) == NULL)
		{
			printf("Input/Output file does not exist.\n");
			continue;
		}
		if(!translate())
		{
			printf("The output data is invalid.\n");
			Nothing(i);
			continue;
		}
		printf("Successful!\n");
		Case(i);
		fclose(fin); fclose(fout);
	}
	end();
	fclose(fstd);
}
