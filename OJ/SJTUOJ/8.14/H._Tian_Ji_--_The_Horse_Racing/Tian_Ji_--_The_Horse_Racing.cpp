#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <iostream>
#include <math.h>
#include <assert.h>
#include <vector>
#include <queue>
#include <string>
#include <map>
#include <set>

using namespace std;
typedef long long ll;
typedef unsigned int uint;
typedef unsigned long long ull;
static const double EPS = 1e-9;
static const double PI = acos(-1.0);

#define REP(i, n) for (int i = 0; i < (int)(n); i++)
#define FOR(i, s, n) for (int i = (s); i < (int)(n); i++)
#define FOREQ(i, s, n) for (int i = (s); i <= (int)(n); i++)
#define FORIT(it, c) for (__typeof((c).begin())it = (c).begin(); it != (c).end(); it++)
#define MEMSET(v, h) memset((v), h, sizeof(v))
#define PB push_back
#define GU(a, b) if ((a)>(b)) (b)=(a);
#define SU(a, b) if ((a)<(b)) (b)=(a);
#define MID(l, r) (((l)+(r))>>1)

/*class MincostMaxflow{
private:*//*
	static const int MAXV = 5003;
	static const int MAXE = 5000006;
	static const int INF = 0x3fffffff;
	int pos,head[MAXV],next[MAXE],e[MAXE],cap[MAXE],flow[MAXE],val[MAXE];
	int dist[MAXV],pre[MAXV],q[MAXE];
	bool visit[MAXV];
	bool spfa(int s, int t,int n)
	{
		memset(pre,-1,sizeof(pre));
		fill(dist,dist+n,0x3fffffff);
		memset(visit,false,sizeof(visit));
		int start=0,end =0;
		q[end++] = s;
		dist[s] =0;
		visit[s] = true;
		while(start < end)
		{
			int u = q[start++];
			visit[u] = false;
			for(int i = head[u]; i != -1; i = next[i])
			{

				if(dist[e[i]] > dist[u] + val[i] && cap[i] - flow[i] >0)
				{
					pre[e[i]] = i;
					dist[e[i]] = dist[u] + val[i];
					if(!visit[e[i]])
					{
						visit[e[i]] = true;
						q[end++] = e[i];
					}
				}
			}
		}
		return pre[t] !=-1;
	}
//public:
	void clear()
	{
		memset(head,-1,sizeof(head));
		memset(flow,0,sizeof(flow));
		pos = 0;
	}
	void add(int s,int t,int capacity,int value)
	{
		e[pos]=t;
		cap[pos] = capacity;
		val[pos] = value;
		next[pos] = head[s];
		head[s] = pos++;

		e[pos] = s;
		cap[pos] = 0;
		val[pos] = -value;
		next[pos] = head[t];
		head[t] = pos++;
	}
	int getmaxflow(int s,int t,int n)
	{
		int total_flow = 0;
		while(spfa(s,t,n))
		{
			int max_flow = INF;
			int cur = t;
			while(cur != s)
			{
				if(max_flow > cap[pre[cur]] - flow[pre[cur]])
					max_flow = cap[pre[cur]] - flow[pre[cur]];
				cur = e[pre[cur]^1];
			}
			total_flow += max_flow;
			cur =t;
			while(cur != s)
			{
				flow[pre[cur]] += max_flow;
				flow[pre[cur]^1] -= max_flow;
				cur = e[pre[cur]^1];
			}
		}
		return total_flow;
	}
	int getmincost()
	{
		int cost=0;
		for(int i =0; i <pos; i++)
			if(flow[i] > 0) {
				cost += flow[i]*val[i];
				//printf("flow: %d, val: %d, e: %d\n", flow[i], val[i], e[i]);
			}
		return cost;
	}
//}costflow;
*/
inline int lowbit(int x) { return x&(-x); }
inline int mgcd(int x, int y) { return y?mgcd(y, x%y):x; }

inline int cmp(int x, int y) {
	if (x>y) return 1;
	else if (x==y) return 0;
	else return -1;
}

const int V=5003, E=3000006, maxint=0x3F3F3F3F;

struct etype
{
    int t, c, u;
    etype *next, *pair;
    etype() {}
    etype(int T, int C, int U, etype* N): t(T), c(C), u(U), next(N) {}
    void* operator new(unsigned, void* p){return p;}
} *e[V], Te[E+E], *Pe;

int S, T, n, piS, cost;
bool v[V];

void addedge(int s, int t, int u, int c)
{
    e[s] = new(Pe++) etype(t, +c, u, e[s]);
    e[t] = new(Pe++) etype(s, -c, 0, e[t]);
    e[s]->pair = e[t];
    e[t]->pair = e[s];
}

int aug(int no, int m)
{
    if (no == T) return cost += piS * m, m;
    v[no] = true;
    int l = m;
    for (etype *i = e[no]; i; i = i->next)
        if (i->u && !i->c && !v[i->t])
        {
            int d = aug(i->t, l < i->u ? l : i->u);
            i->u -= d, i->pair->u += d, l -= d;
            if (!l) return m;
        }
    return m - l;
}

bool modlabel()
{
    static int d[V]; REP(i, n) d[i]=maxint; d[T] = 0;
    static deque<int> Q; Q.push_back(T);
    while(Q.size())
    {
        int dt, no = Q.front(); Q.pop_front();
        for(etype *i = e[no]; i; i = i->next)
            if(i->pair->u && (dt = d[no] - i->c) < d[i->t])
                (d[i->t] = dt) <= d[Q.size() ? Q.front() : 0]
                    ? Q.push_front(i->t) : Q.push_back(i->t);
    }
    for(int i = 0; i < n; ++i)
        for(etype *j = e[i]; j; j = j->next)
            j->c += d[j->t] - d[i];
    piS += d[S];
    return d[S] < maxint;
}

int tj[5003], ki[5003];

int main() {
	while (scanf("%d", &n), n) {
		REP(i, n*2+2) e[i]=0;
        Pe = Te;
		REP(i, n) {
			addedge(n*2, i, 1, 0);
			scanf("%d", &tj[i]);
		}
		REP(i, n) {
			addedge(n+i, n*2+1, 1, 0);
			scanf("%d", &ki[i]);
		}
		REP(i, n) REP(j, n) addedge(i, n+j, 1, -cmp(tj[i], ki[j]));
		S=n*2, T=n*2+1, n=n*2+2;
		piS = cost = 0;
        while(modlabel())
            do REP(i, n) v[i]=0;
            while(aug(S, maxint));
		printf("%d\n", -cost*200);
	}
	return 0;
}
