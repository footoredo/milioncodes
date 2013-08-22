#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

double swap(double a, double b) {
	double t=a; a=b; b=t;
}
typedef long long ll;
typedef unsigned int uint;
typedef unsigned long long ull;
const double EPS = 1e-9;
const double PI = acos(-1.0);

int check(int A, int B, double X, double Y) {
	if (A>B+EPS) swap(A, B);
	if (X>Y+EPS) swap(X, Y);
	if (X+EPS<A&&Y+EPS<B) return 1;
	else return 0;
}

const int S = 10;
int A, B;
double X, Y;

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d%d%lf%lf",&A,&B,&X,&Y);
		int res=0;
		int i;
		for (i=0;i<=90*S;++i) {
			double a = Y*sin(i*1.0/S*PI/180.0);
			double b = sqrt(Y*Y-a*a);
			if (check(A,B,a+b/Y*X,b+a/Y*X)==1) {
				res = 1; break;
			}
		}
		if (res==1) printf("Escape is possible.\n");
		else printf("Box cannot be dropped.\n");
	}
	return 0;
}
