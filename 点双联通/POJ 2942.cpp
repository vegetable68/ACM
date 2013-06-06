//dot bi-connected
//POJ2942
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <stack>
#include <cstring>
#include <string>
#include <algorithm>
#define MaxN 1005
using namespace std;

int N, M, x, y, tag[MaxN], cnt, dfn[MaxN], Ti, ok[MaxN], col[MaxN], Ans, low[MaxN], now;
bool hos[MaxN][MaxN];
vector<int> g[MaxN], L;
stack<int> S;

bool color(int cur, int x){
	col[cur] = x;
	for (int i = 0; i < g[cur].size(); i ++){
		int succ = g[cur][i];
		if (tag[succ] != cnt) continue;
		if (col[succ] == x) return 1;
		if (col[succ] == -1 && color(succ, x^1)) return 1;
	}
	return 0;
}

void Check(){

	for (int i = 0; i < L.size(); i ++) col[L[i]] = -1;
	if (color(L[0], 0)){
		for (int i = 0; i < L.size(); i ++) ok[L[i]] = 1;
	}
}

void DFS(int cur){
	dfn[cur] = low[cur] = ++Ti;
	S.push(cur);
	for (int i = 0; i < g[cur].size(); i ++){
		int succ = g[cur][i];
		if (dfn[succ] < 0){
			DFS(succ);
			if (low[succ] >= dfn[cur]){
				cnt ++; L.clear();
				do{
					now = S.top();
					tag[now] = cnt;
					L.push_back(now);
					S.pop();
				}while (now != succ);
				L.push_back(cur);
				tag[cur] = cnt;
				Check();
			}
			low[cur] = min(low[cur], low[succ]);
		}else low[cur] = min(low[cur], dfn[succ]);
	}
}

int main(){
	scanf("%d%d", &N, &M);
	while (N || M){
		memset(hos, 0, sizeof(hos));
		for (int i = 0; i < M; i ++){
			scanf("%d%d", &x, &y); 
			x --; y --;
			hos[x][y] = hos[y][x] = 1;
		}
		for (int i = 0; i < N; i ++){g[i].clear(); tag[i] = -1; dfn[i] = -1; ok[i] = 0;}
		for (int i = 0; i < N; i ++)
			for (int j = 0; j < N; j ++)
				if (i != j && !hos[i][j]) g[i].push_back(j);

		cnt = 0; Ti  = 0;
		for (int i = 0; i < N; i ++){
			while (!S.empty()) S.pop();
			if (dfn[i] < 0) DFS(i);
		}
		Ans = 0;
		for (int i = 0; i < N; i ++) Ans += (!ok[i]);
		printf("%d\n", Ans);
		scanf("%d%d", &N, &M);
	}
}
