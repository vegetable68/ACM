//leftest tree
//ZOJ2334
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <string>
#include <algorithm>
#define MaxN 100010
using namespace std;

struct node{
		int val, rch, lch, fa, dist;
	}g[MaxN];

int M, N, x, y, fx, fy, Ans, tmp;

int getf(int x){
	while (g[x].fa != x) x = g[x].fa;
	return x;
}

int merge(int x, int y){
	if (x == -1) return y;
	if (y == -1) return x;
	if (g[x].val < g[y].val) swap(x,y);
        g[x].rch = merge(g[x].rch, y);
	if (g[x].rch != -1) g[g[x].rch].fa = x; 
	if (g[x].lch == -1 || (g[x].rch != -1 && g[g[x].lch].dist < g[g[x].rch].dist))
		swap(g[x].lch, g[x].rch);
	if (g[x].rch == -1) g[x].dist = 1; 
		else g[x].dist = g[g[x].rch].dist + 1;	
	return x;
}

int down(int x){
    if (g[x].lch >= 0) g[g[x].lch].fa = g[x].lch;
    if (g[x].rch >= 0) g[g[x].rch].fa = g[x].rch;
    tmp = merge(g[x].lch, g[x].rch);
    g[x].lch = -1; g[x].rch = -1; g[x].dist = 1; g[x].fa = x;
	return merge(tmp, x);    
}

int main(){
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
	while (scanf("%d", &N)!= -1){
	      for (int i = 0; i < N; i ++){
		      scanf("%d", &g[i].val);
		      g[i].rch = -1; g[i].lch = -1;
		      g[i].fa = i; g[i].dist = 1;
	       }
	       scanf("%d", &M);
           for (int i = 0; i < M; i ++){
		       scanf("%d %d", &x, &y);
		       x --; y --; fx = getf(x); fy = getf(y);
               if (fx == fy) printf("-1\n"); 
			   else {
				    g[fx].val /= 2; fx = down(fx);
				    g[fy].val /= 2; fy = down(fy);
				    tmp = merge(fx, fy);
				    printf("%d\n", g[tmp].val);
			     }
           }
    }
}
