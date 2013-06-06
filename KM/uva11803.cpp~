//KM
//uva11803
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#define MaxN 205
#define oo 1000000000
using namespace std;

int All, lack, Task, Case, N[5], F[5][MaxN], S[5][MaxN], Ans[MaxN][MaxN], w[MaxN][MaxN], lx[MaxN], ly[MaxN], linky[MaxN];
bool visx[MaxN], visy[MaxN];
vector<int> T[5][MaxN];

bool find(int cur, int All){
	visx[cur] = 1;
//	cout<<cur<<" "<<All<<endl;
	for (int i = 0; i < All; i ++){
		if (visy[i]) continue;
		int tmp = lx[cur] + ly[i] - w[cur][i];
	//	cout<<cur<<" "<<lx[cur]<<" "<<ly[i]<<" "<<w[cur][i]<<endl;
		if (tmp == 0){
			visy[i] = 1;
//			cout<<cur<<" "<<i<<endl;
			if (linky[i] == -1 || find(linky[i], All)){
				linky[i] = cur; return 1;
			}
		}else lack = min(lack, tmp);
	}
	return 0;
}

int calc(int All){
//	cout<<All<<endl;
	for (int i = 0; i < All; i ++) lx[i] = -1000000000;
	for (int i = 0; i < All; i ++)
		for (int j = 0; j < All; j ++)
			lx[i] = max(lx[i], w[i][j]);
	memset(linky, -1, sizeof(linky));
	memset(ly, 0, sizeof(ly));
	for (int i = 0; i < All; i ++){
		for (;;){
			memset(visx, 0, sizeof(visx));
			memset(visy, 0, sizeof(visy));
			lack = oo;
			//cout<<i<<":"<<endl;
			if (find(i, All)) break;
			for (int j = 0; j < All; j ++){
				if (visx[j]) lx[j] -= lack;
				if (visy[j]) ly[j] += lack;
			}
		}
	}

//	for (int j = 0; j < All; j ++) cout<<j<<" "<<linky[j]<<endl;
	int Ans = 0;
	for (int i = 0; i < All; i ++) Ans += lx[i] + ly[i];
	
	return Ans;
}

void dp(int x, int y){
	int Num0 = T[0][x].size(), Num1 = T[1][y].size(), All = max(Num0, Num1);
	for (int i = 0; i < Num0; i ++)
		for (int j = 0; j < Num1; j ++)
			dp(T[0][x][i], T[1][y][j]);
	
	for (int i = 0; i < All; i ++)
		for (int j = 0; j < All; j ++){
			if (i < Num0 && j < Num1){
				w[i][j] = -Ans[ T[0][x][i] ][ T[1][y][j] ];
			}else{
				if (i >= Num0) w[i][j] = -S[1][ T[1][y][j] ];
					else w[i][j] = -S[0][ T[0][x][i] ];
			}
//			if (x == 1 && y == 1) cout<<i<<" "<<j<<" "<<":"<<w[i][j]<<endl;
		}
	Ans[x][y] = -calc(All);
//	cout<<x<<" "<<y<<":"<<Ans[x][y]<<endl;
}

void dfs(int lab, int cur){
	S[lab][cur] = 1;
	for (int i = 0; i < T[lab][cur].size(); i ++){
		int succ = T[lab][cur][i];
		dfs(lab, succ);
		S[lab][cur] += S[lab][succ];
	}
}

int main(){
	scanf("%d", &Task); Case = 0;
	while (Task--){
		memset(S, 0, sizeof(S));
		for (int i = 0; i < 2; i ++)
			for (int j = 0; j < MaxN; j ++) T[i][j].clear();
		for (int z = 0; z < 2; z ++){
			scanf("%d", &N[z]);
			for (int i = 1; i <= N[z]; i ++){
				scanf("%d", &F[z][i]);
				T[z][F[z][i]].push_back(i);
			}
		}
		memset(Ans, -1, sizeof(Ans));
		dfs(0, 0); dfs(1, 0); 
		
//		return 0;

		dp(0, 0);
		printf("Case %d: %d\n", ++Case, Ans[0][0]);
	}
}
