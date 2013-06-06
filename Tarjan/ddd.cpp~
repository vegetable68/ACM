//http://acm.student.cs.uwaterloo.ca/~acm00/081004/
//Tarjan 非递归

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#define MaxN 200005
using namespace std;

int Task, N, M, cnt, Ti, tag[MaxN], dfn[MaxN], low[MaxN], top, S[MaxN], Ans, x, y, Sum[MaxN], 
	SS[MaxN], Stop;
vector<int> g[MaxN];
bool instack[MaxN], hS[MaxN];

void dfs(int cur){
	SS[Stop = 1] = cur;
	dfn[cur] = low[cur] = ++Ti;
	S[++top] = cur; instack[cur] = 1;
	while (Stop){
		int tmp = SS[Stop];
		//cout<<tmp<<endl;
		for (int i = 0; i < g[tmp].size(); i ++){
			int succ = g[tmp][i];
			if (dfn[succ] == -1){
				dfn[succ] = low[succ] = ++Ti;
				S[++top] = succ; instack[succ] = 1;			
				SS[++Stop] = succ;
			}
		}
		//cout<<SS[Stop]<<endl;
		if (SS[Stop] == tmp){
			for (int i = 0; i < g[tmp].size(); i ++){
				int succ = g[tmp][i];
				if (dfn[succ] > dfn[tmp]){
					low[tmp] = min(low[tmp], low[succ]);
				}else if (instack[succ]) low[tmp] = min(low[tmp], dfn[succ]);
			}
			if (dfn[tmp] == low[tmp]){
				cnt ++;
				while (S[top + 1] != tmp){
					instack[S[top]] = 0;
					tag[S[top--]] = cnt;
				}
			}
			Stop --;
		}
	}
}

int main(){
	scanf("%d", &Task);
	while (Task--){
		scanf("%d%d", &N, &M);
		for (int i = 0; i <= N; i ++){
			g[i].clear(); dfn[i] = low[i] = S[i] = tag[i] = -1;
			instack[i] = 0;
		}
		cnt = Ti = 0;
		for (int i = 0; i < M; i ++){
			scanf("%d%d", &x, &y); x--; y --;
			g[x].push_back(y);
		}
		//return 0;
		
		for (int i = 0; i < N; i ++){
			if (dfn[i] == -1){
				top = 0; dfs(i);
			}
			//cout<<i<<" "<<tag[i]<<endl;
		}
		for (int i = 0; i <= cnt; i ++) Sum[i] = 0;
		for (int i = 0; i < N; i ++)
			for (int j = 0; j < g[i].size(); j ++){
				//cout<<i<<" "<<g[i][j]<<" "<<tag[i]<<" "<<tag[g[i][j]]<<endl;
				if (tag[i] != tag[g[i][j]]) Sum[tag[g[i][j]]] ++;
			}
		Ans = 0;
		for (int i = cnt; i >= 1; i --){
		//	cout<<Sum[i]<<endl;
			if (Sum[i]) continue; Ans ++;
		}
		printf("%d\n", Ans);
	}
}
