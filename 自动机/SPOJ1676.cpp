//automation
//SPOJ1676
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
#define MOD 10007
#define LL long long
#define LD long double
using namespace std;
      
int N, L, ANS, W[10], Pre, tot, Sum;
string S;
vector<int> h;

struct node{
            int pos[30], accept, fa, rep, pre, lab;
            node(){memset(pos, 0, sizeof(pos)); accept = 0; fa = 0; rep = 0; pre = 0; lab = 0;} 
       };
       
struct Matrix{
              int a[65][65], r, c;
              Matrix(){memset(a, 0, sizeof(a)); r = c = 0;}
              void clear(){memset(a, 0, sizeof(a)); r = c = 0;}
              Matrix operator * (const Matrix &T)const{
                     Matrix res;
                     res.r = r; res.c = T.c;
                     for (int i = 0; i < res.r; i ++)
                         for (int j = 0; j < res.c; j ++)
                             for (int k = 0; k < c; k ++){
                                 int tmp = a[i][k] * T.a[k][j];
                                 tmp = tmp - int(tmp / MOD) * MOD;
                                 tmp = res.a[i][j] + tmp;
                                 tmp = tmp - int(tmp / MOD) * MOD;
                                 res.a[i][j] = tmp;
                             }   
                     return res;
              }
              void print(){
                   cout<<r<<" "<<c<<endl;
                   for (int i = 0; i < r; i ++){
                       for (int j = 0; j < c; j ++) cout<<a[i][j]<<" ";
                       cout<<endl;
                   }
              }
       }cur, Ans, C;

struct Automaton{
                 vector<node> g;
                 queue<int> Q;
                 int Size, cur, p;
                 Automaton(){g.clear(); node tmp; g.push_back(tmp); Size = 1;}
                 void clear(){g.clear(); node tmp; g.push_back(tmp); Size = 1;}
                 int ins(int cur, int P){
                      if (W[cur] == -1) {g[P].accept |= 1; return -1;}
                      if (!g[P].pos[W[cur]]){
                         node tmp; g.push_back(tmp);
                         g[P].pos[W[cur]] = Size; g[Size].fa = P;
                         g[Size].rep = W[cur]; Size ++;
                      }
                      return g[P].pos[W[cur]];
                    //  ins(cur + 1, g[P].pos[W[cur]]);
                 }
                 void fix(){
                      while (!Q.empty()) Q.pop();
                      Q.push(0);
                      while (!Q.empty()){
                            cur = Q.front();
                            if (g[cur].fa == 0)
                               g[cur].pre = 0;
                            else{
                                 p = g[g[cur].fa].pre;
                                 while (p && !g[p].pos[g[cur].rep]) p = g[p].pre;
                                 g[cur].pre = g[p].pos[g[cur].rep];
                            }
                            g[cur].accept |= g[g[cur].fa].accept;
                            g[cur].accept |= g[g[cur].pre].accept;
                            if (!g[cur].accept){
                               h.push_back(cur);
                               g[cur].lab = h.size() - 1;
                            }else g[cur].lab = -1;
                            for (int i = 0; i < 26; i ++) 
                                if (g[cur].pos[i])
                                   Q.push(g[cur].pos[i]);
                                else g[cur].pos[i] = g[g[cur].pre].pos[i];
                            Q.pop();
                      }
                 }
                 int Nxt(int cur, int nxt){
                     return g[g[cur].pos[nxt]].lab;
                 }
       }T;
       
void calc(Matrix &cur, int T){
       if (T == 1) return;
       calc(cur, T / 2);
       cur = cur * cur;
       if (T & 1) cur = cur * C;
}

void GetS(){
       tot = 0; 
       char ch = getchar();
       while (ch != '\n'){
             W[tot++] = ch - 'A';
             ch = getchar();
       }
       W[tot] = -1;
}
      
int main(){
     //   freopen("in.txt", "r", stdin);
     //   freopen("out.txt", "w", stdout);
        while (scanf("%d %d\n", &N, &L) > 0){
             // cout<<N<<" "<<L<<endl;
              T.clear();
              for (int i = 0; i < N; i ++){
                  GetS(); Pre = 0;
                  for (int j = 0; j <= tot; j ++) Pre = T.ins(j, Pre);
              }
              h.clear();
              T.fix(); Sum = h.size();
          //    cout<<T.g[0].accept<<endl;
         //     cout<<Sum<<endl;
              cur.clear(); cur.r = Sum + 1; cur.c = Sum + 1;
              for (int i = 0; i < Sum; i ++)
                  for (int j = 0; j < 26; j ++){
                      if (T.Nxt(h[i], j) < 0)
                         cur.a[i][Sum] ++;
                      else cur.a[i][T.Nxt(h[i], j)] ++;
                  }
              cur.a[Sum][Sum] = 26;
           //   cur.print();
              Ans.clear(); Ans.r = 1; Ans.c = Sum + 1; Ans.a[0][0] = 1;
              C = cur;
              calc(cur, L);
            //  cur.print();
              Ans = Ans * cur;
            //  Ans.print();
              printf("%d\n", Ans.a[0][Sum]);
        }
        //system("pause");
}
