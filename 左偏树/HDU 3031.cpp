//leftest tree
//HDU 3031
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <string>
#include <algorithm>
#include <queue>
#include <set>
#include <map>
#include <cmath>
#define LL long long
#define LD long double
using namespace std;

struct node{
            int lch, rch, dist, val;
            node(int _v = -1){lch = rch = -1; dist = 1; val = _v;}
       }cur;

int R, Score_w, Score_h, N, M, P[105], Px, tag, C[105], Player[5], Sum[5];
vector<node> g;
char ch;

int merge(int x, int y){
    if (x == -1) return y;
    if (y == -1) return x;
    if (g[x].val < g[y].val) swap(x, y);
    g[x].rch = merge(g[x].rch, y);
    if (g[x].lch == -1 || (g[x].rch != -1 && g[g[x].rch].dist > g[g[x].lch].dist))
       swap(g[x].lch, g[x].rch);
    if (g[x].rch == -1) g[x].dist = 1; else g[x].dist = g[g[x].rch].dist + 1;
    return x;
}

int Del(int x){
    g[x].lch = g[x].rch = -1;
    return merge(g[x].lch, g[x].rch);
}

int main(){
        freopen("in.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
        while (scanf("%d", &R) != -1){
              Score_w = Score_h = 0; g.clear();
              for (int z = 0; z < R; z ++){
                  scanf("%d %d", &N, &M);
                  for (int i = 0; i < M; i ++) scanf("%d", &P[i]);
                  for (int i = 0; i < M; i ++){
                      C[i] = -1;
                      for (int j = 0; j < P[i]; j ++){
                          scanf("%d", &Px);
                          cur = node(Px); g.push_back(cur);
                          C[i] = merge(C[i], g.size() - 1);
                      }
                  }
                  scanf("\n");
                  for (int i = 0; i < 2; i ++) Player[i] = -1;
                  Sum[0] = Sum[1] = 0;
                  for (int i = 0; i < N; i ++){
                      tag = i % 2;
                      scanf("%c", &ch);
                      if (ch == 'T'){
                         scanf("%d\n", &Px); 
                         Px --;
                         Player[tag] = merge(Player[tag], C[Px]);
                         Sum[tag] += P[Px];
                         continue;
                      }
                      if (ch == 'C'){
                         scanf("\n");
                         if (g[Player[0]].val == g[Player[1]].val) continue;
                         if (g[Player[0]].val > g[Player[1]].val){
                            Player[0] = merge(Player[0], Player[1]);
                            Sum[0] += Sum[1]; Sum[1] = 0;
                            Player[1] = -1; continue;
                         }else{
                               Player[1] = merge(Player[0], Player[1]);
                               Sum[1] += Sum[0]; Sum[0] = 0;
                               Player[0] = -1; continue;
                         }
                      }
                      if (ch == 'L'){
                         scanf("\n");
                         Player[tag] = Del(Player[tag]);
                         Sum[tag] --;
                         continue;
                      }
                      if (ch == 'A'){
                         scanf("%d\n", &Px);
                         g[Player[tag]].val += Px; continue;
                      }
                      if (ch == 'E'){
                         scanf("%d\n", &Px);
                         Player[tag] = Del(Player[tag]);
                         cur = node(Px);
                         g.push_back(cur); Player[tag] = merge(Player[tag], g.size() - 1);
                      }
                  }
                  printf("%d:%d\n", Sum[0], Sum[1]);
                  if (Sum[0] >= Sum[1]) Score_w ++; else Score_h ++;
              }
              if (Score_w >= Score_h) printf("Hahaha...I win!!\n");
                 else printf("I will be back!!\n");
        }
        //system("pause");
}
