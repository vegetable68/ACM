//automation
//Timus1158
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
#define MaxN 55
#define MaxL 105
using namespace std;

int N, L, M, W[15], tot, Ntot;
string S, cur;

struct node{
            int d[MaxL], Len, pos;
            bool tag;
            node(){memset(d, 0, sizeof(d)); Len = 1; tag = false;}
            void clear(){memset(d, 0, sizeof(d)); Len = 1; tag = false;}
            node operator + (const node &x)const{
                 node Res;
                 Res.Len = max(Len, x.Len);
                 for (int i = 0; i < Res.Len; i ++)
                     Res.d[i] = d[i] + x.d[i];
                 for (int i = 0; i < Res.Len; i ++){
                     Res.d[i + 1] = Res.d[i + 1] + Res.d[i] / 10;
                     Res.d[i] %= 10;
                 }
                 if (Res.d[Res.Len]) Res.Len ++;
                 return Res;
            }
            void print(){
                 for (int i = Len - 1; i >= 0; i --) printf("%d", d[i]);
                 printf("\n");
            }
       }f[MaxN][105], Ans;

struct point{
               int pos[MaxN], forbid, pre, fa, rep;
               point(){memset(pos, 0, sizeof(pos)); forbid = 0; pre = 0; fa = 0; rep = 0;}
       };

struct Automaton{
                 int Size, cur, p;
                 vector<point> g;
                 queue<int> Q;
                 Automaton(){g.clear(); Size = 1; point tmp; g.push_back(tmp);}
                 void ins(int W[], int cur, int P){
                      if (W[cur] == -1) {g[P].forbid |= 1; return;}
                      if (!g[P].pos[W[cur]]){
                         point tmp; g.push_back(tmp); 
                         g[Size].fa = P; g[Size].rep = W[cur]; 
                         g[P].pos[W[cur]] = Size; Size ++;
                      }
                      ins(W, cur + 1, g[P].pos[W[cur]]);
                 }
                 void fix(int N){
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
                            g[cur].forbid |= g[g[cur].fa].forbid;
                            g[cur].forbid |= g[g[cur].pre].forbid;
                            for (int i = 0; i < N; i ++)
                                if (g[cur].pos[i]) Q.push(g[cur].pos[i]);
                                   else g[cur].pos[i] = g[g[cur].pre].pos[i];
                            Q.pop();
                          //  cout<<cur<<endl;
                      }
                 }
                 int Nxt(int cur, int nxt){
                     return g[cur].pos[nxt];
                 }
       }T;
       
int Deal(char ch){
    for (int i = 0; i < N; i ++) if (S[i] == ch) return i;
}

int main(){
      //  freopen("in.txt", "r", stdin);
     //   freopen("out.txt", "w", stdout);
        scanf("%d %d %d\n", &N, &L, &M);
        getline(cin, S);
    //    cout<<M<<endl;
        for (int i = 0; i < M; i ++){
            getline(cin, cur);
         //   cout<<i<<" "<<M<<endl;
            for (int j = 0; j < cur.length(); j ++) W[j] = Deal(cur[j]);
            W[cur.length()] = -1;
            T.ins(W, 0, 0);
        }
      //  cout<<"tag"<<endl;
      //  cout<<T.g[3].pre<<endl;
        T.fix(N); f[0][0].tag = 1;
      //  cout<<"__________"<<endl;
      //  cout<<T.g[3].pre<<endl;
        f[0][0].d[0] = 1;
     //   f[0][0].print();
        for (int i = 0; i < L; i ++){
             for (int j = 0; j < T.Size; j ++){
                 if (!f[i][j].tag || T.g[j].forbid) continue;
                 for (int k = 0; k < N; k ++){
                     int tmp = T.Nxt(j, k);
                   //  cout<<j<<" "<<k<<" "<<tmp<<endl;
                     f[i + 1][tmp] = f[i + 1][tmp] + f[i][j];
                     f[i + 1][tmp].tag |= 1;
                 }
                // cout<<i<<" "<<j<<":";
             //    f[i][j].print();
             }
        }
     //   cout<<"tag"<<endl;
        Ans.clear();
        for (int i = 0; i < T.Size; i ++) 
            if (f[L][i].tag && !T.g[i].forbid) Ans = Ans + f[L][i];
        Ans.print();
        //system("pause");
}
