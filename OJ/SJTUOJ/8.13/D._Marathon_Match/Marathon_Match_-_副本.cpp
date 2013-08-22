

const int N = 102, M=600005;

int tp[N], rt[N], v[N];
double p[N], ans[N], sum[N][M], f[N][M];
ll c[102][102];

void calcc(int n) {
	c[0][0]=1;
	for (int i=1; i<=n; ++i) {
		c[i][0]=1;
		for (int j=1; j<=i; ++j) c[i][j]=c[i-1][j]+c[i-1][j-1];
	}
}

int main() {
	int n, m, L; scanf("%d%d%d", &n, &m, &L);
	calcc(m); bool tk;
	REP(i, n) {
		scanf("%d%d%d", &tp[i], &rt[i], &v[i]);
		p[i]=tp[i]/100.0;
		double pp=1;
		REP(j, m) pp*=(1-p[i]);
		REP(j, m+1) {
			f[i][j*rt[i]]+=c[m][j]*pp;
			pp=pp/(1-p[i])*p[i];
		}
		for (int j=m*rt[i]; j>=0; --j)
			sum[i][j]=sum[i][j+1]+f[i][j];
	}
	REP(i, n) {
		if (v[i]==0) { printf("0.0000000\n"); continue; }
		ans[i]=0;
		REP(j, m+1) {
			if (rt[i]==0&&j) break;
			double tans=1;
			REP(k, n) if (i!=k) {
				double t=L*1.0/v[i]+j*rt[i]-L*1.0/v[k];
				int tt; if (t<0) tt=0; else tt=(int)ceil(t);
				if (t+EPS>=tt) ++tt;
				tans*=f[i][j*rt[i]]*sum[k][tt];
			}
			ans[i]+=tans;
		}
		printf("%.7f\n", ans[i]);
	}
	return 0;
}
