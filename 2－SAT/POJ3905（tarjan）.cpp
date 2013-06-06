//2-SAT 
//Tarjan
//POJ3905
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <stack>
#include <cstring>
#include <string>
#include <algorithm>
#define MaxN 1005
#define PII pair<int, int>
#define MP make_pair
#define x first
#define y second
using namespace std;

int N, M, lab_x, lab_y, tag_x, tag_y, low[MaxN][5], dfn[MaxN][5], cnt, tag[MaxN][5], Ti, top;
vector<PII> g[MaxN][5];
char chx, chy;
bool instack[MaxN][5];
PII nxt, S[MaxN * 10];

void connect(int lx, int tx, int ly, int ty){
	g[lx][tx].push_back(MP(ly, ty));
}

void dfs(PII cur){
	dfn[cur.x][cur.y] = low[cur.x][cur.y] = ++Ti;
	S[++top] = cur; instack[cur.x][cur.y] = 1;
	for (int i = 0; i < g[cur.x][cur.y].size(); i ++){
		nxt = g[cur.x][cur.y][i];
		if (dfn[nxt.x][nxt.y] == -1){
			dfs(nxt);
			low[cur.x][cur.y] = min(low[cur.x][cur.y], low[nxt.x][nxt.y]);
		}else if (instack[nxt.x][nxt.y]) low[cur.x][cur.y] = min(low[cur.x][cur.y], dfn[nxt.x][nxt.y]);
	}
	if (low[cur.x][cur.y] == dfn[cur.x][cur.y]){
		cnt ++;
		do{
			tag[S[top].x][S[top].y] = cnt;
			instack[S[top].x][S[top].y] = 0;
			top --;
		}while (S[top + 1] != cur);			
	}
}

int isok(){
	for (int i = 0; i < N; i ++)
		if (tag[i][0] == tag[i][1]) return 0;
	return 1;
}

int Abs(int x){
	return x < 0 ? -x:x;
}

int main(){
	while (scanf("%d%d ", &N, &M) != -1){
		for (int i = 0; i < N; i ++)
			for (int j = 0; j < 2; j ++){
				g[i][j].clear();
				dfn[i][j] = low[i][j] = tag[i][j] = -1;
			}
		for (int i = 0; i < M; i ++){
			scanf("%d%d", &lab_x, &lab_y);
			//cout<<lab_x<<" "<<lab_y<<endl;
			if (lab_x > 0) tag_x = 1; else tag_x = 0;
			if (lab_y > 0) tag_y = 1; else tag_y = 0;
			lab_x = Abs(lab_x); lab_y = Abs(lab_y); lab_x --; lab_y --;
			connect(lab_x, tag_x^1, lab_y, tag_y);
			connect(lab_y, tag_y^1, lab_x, tag_x);
			//cout<<lab_x<<" "<<lab_y<<" "<<tag_x<<" "<<tag_y<<endl;
		}
	/*	for (int i = 0; i < N; i ++)
			for (int j = 0; j < 2; j ++){
				cout<<i<<","<<j<<":";
				for (int k = 0; k < g[i][j].size(); k ++) cout<<"("<<g[i][j][k].x<<","<<g[i][j][k].y<<")";
				cout<<endl;
			}*/
		//cout<<"tag"<<endl;
		cnt = Ti = 0;
		for (int i = 0; i < N; i ++)
			for (int j = 0; j < 2; j ++)
				if (dfn[i][j] == -1){
					top = 0;
					memset(instack, 0, sizeof(instack));
					dfs(MP(i, j));
				}
	/*	for (int i = 0; i < N; i ++){
			for (int j = 0; j < 2; j ++) cout<<tag[i][j]<<" ";
			cout<<endl;
		}*/
		printf("%d\n", isok());
	}
}
