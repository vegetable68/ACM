//SAP
//POJ3498
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <algorithm>
#define oo 100000
#define MaxN 305
using namespace std;

struct Penguin{
		int in, out;
		double x, y;
		void In(){
			scanf("%lf%lf%d%d", &x, &y, &in, &out);
		}
	}P[MaxN];
	
struct Edge{
		int des, cap, nxt;
		Edge(int _d = 0, int _c = 0, int _n = 0):des(_d), cap(_c), nxt(_n){}
	}g[30005], tmpg[30005];

int Task, T, N, S, All, tot, e[MaxN * 3], d[MaxN * 3], vd[MaxN * 3], Ans, Sum;
double D;
vector<int> ULTI;

void connect(int x, int y, int _cap){
	g[tot] = Edge(y, _cap, e[x]); e[x] = tot ++;
}

int sap(int u, int v, int flow){
	int sum = 0, tmp, M = All + 1;
	if (u == v) return flow;
	for (int i = e[u]; i != -1; i = g[i].nxt){
		int succ = g[i].des;
		if (!g[i].cap) continue;
		if (d[succ] + 1 == d[u] && (flow - sum)){
			tmp = min(flow - sum, g[i].cap);
			tmp = sap(succ, v, tmp);
			sum += tmp; g[i].cap -= tmp; g[i^1].cap += tmp;
			if (d[S] >= All) return sum;
		} 
		M = min(d[succ] + 1, M);
	}
	if (sum) return sum;
	vd[d[u]] --;
	if (!vd[d[u]]) d[S] = All;
	vd[M] ++; d[u] = M;
	return sum;
}

double sqr(double x){
	return x * x;
}

double Dis(int x, int y){
	return sqr(P[x].x - P[y].x) + sqr(P[x].y - P[y].y);
}

int main(){
	scanf("%d", &Task);
	while (Task --){
		scanf("%d %lf", &N, &D);
		S = 0; All = 2 * N + 1; Sum = tot = 0; Sum = 0;
		for (int i = 0; i < N; i ++) {P[i].In(); Sum += P[i].in;}
		for (int i = 0; i <= All; i ++) e[i] = -1;
		for (int i = 0; i < N; i ++){
			connect(S, i + 1, P[i].in); connect(i + 1, S, 0);
			connect(i + 1, i + 1 + N, P[i].out);
			connect(i + N + 1, i + 1, 0);
		}
		for (int i = 0; i < N; i ++)
			for (int j = 0; j < N; j ++)
				if (i != j && Dis(i, j)  <= sqr(D)){
					connect(i + 1 + N, j + 1, oo);
					connect(j + 1, i + 1 + N, 0);
				}
		ULTI.clear(); Ans = 0;
		for (int i = 0; i < tot; i ++) tmpg[i] = g[i];
		for (int i = 0; i < N; i ++){
			T = i + 1; Ans = 0;
			for (int j = 0; j <= All; j ++) {d[j] = vd[j] = 0;}
			vd[0] = All;
			while (d[S] < All) Ans += sap(S, T, oo);
			if (Ans == Sum) ULTI.push_back(i);
			for (int j = 0; j < tot; j ++) g[j] = tmpg[j];
		}
		if (ULTI.empty()) printf("-1\n"); else {
			for (int i = 0; i < ULTI.size(); i ++) 
				printf("%d%c", ULTI[i], (i == (ULTI.size() - 1))? '\n' : ' ');
		}
	}
}
