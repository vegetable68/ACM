#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cstring>
#define MaxN 100005
using namespace std;

struct Node{
    int lch, rch, data, dist, fa;
    Node(int _l = -1, int _r = -1, int _d = 0, int _di = 1, int _f = 0):
        lch(_l), rch(_r), data(_d), dist(_di), fa(_f){}
}T[MaxN];
int N, S, M, x, y;

int merge(int x, int y){
    if (x == -1) return y;
    if (y == -1) return x;
    if (T[x].data < T[y].data) swap(x, y);
    T[x].rch = merge(T[x].rch, y);
    if (T[x].rch != -1) T[T[x].rch].fa = x;
    if (T[x].lch == -1 || (T[x].rch != -1 && T[ T[x].lch ].dist < T[ T[x].rch ].dist))
        swap(T[x].lch, T[x].rch);
    if (T[x].rch == -1) T[x].dist = 1; else T[x].dist = T[ T[x].rch ].dist + 1;
    return x;
}

int getf(int x){
    while (T[x].fa != x) x = T[x].fa;
    return x;
}

int down(int x){
    if (T[x].lch != -1) T[ T[x].lch ].fa = T[x].lch;
    if (T[x].rch != -1) T[ T[x].rch ].fa = T[x].rch;
    int tmp = merge(T[x].lch, T[x].rch);
    T[x].lch = -1; T[x].rch = -1; T[x].dist = 1; T[x].fa = x;
    return merge(tmp, x);
}

int main(){
   while (scanf("%d", &N) != -1){
   for (int i = 0; i < N; i ++){
       scanf("%d", &S); T[i] = Node(-1, -1, S, 1, i);
   }
   scanf("%d", &M);
   for (int i = 0; i < M; i ++){
       scanf("%d %d", &x, &y);
       x --; y --;
       int fx = getf(x), fy = getf(y);
       if (fx == fy) {printf("-1\n"); continue;}
       T[fx].data /= 2; int tmpx = down(fx);
       T[fy].data /= 2; int tmpy = down(fy);
       int tmp = merge(tmpx, tmpy);
       printf("%d\n", T[tmp].data);
   }
   }
}
