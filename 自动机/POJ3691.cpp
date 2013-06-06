//automation
//POJ4691
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
using namespace std;

int N, L, f[1010][1010], Si, tmp, Ans, tot;
string cur, S;

struct node{
            int pos[10], tag, pre, fa, ch;
            node(){memset(pos, 0, sizeof(pos)); tag = 0;}
       };

struct Trie{
              int Size, cur, p;
              vector<node> Q;
              queue<int> L;
              Trie(){Q.clear(); node tmp; Q.push_back(tmp); Size = 1; Q[0].fa = 0;}
              void clear(){Q.clear(); node tmp; Q.push_back(tmp); Size = 1; Q[0].fa = 0;}
              void ins(string S, int cur, int P){
                   if (cur == S.length()) {Q[P].tag = 1; return;}
                   if (!Q[P].pos[S[cur] - '0']){
                      node tmp; Q.push_back(tmp); Size ++;
                      Q[Size - 1].fa = P; Q[Size - 1].ch = S[cur] - '0';
                      Q[P].pos[S[cur] - '0'] = Size - 1;
                   }
                   ins(S, cur + 1, Q[P].pos[S[cur] - '0']);
              }
              void fix(){
                   while (!L.empty()) L.pop();
                   L.push(0);
                   while (!L.empty()){
                         cur = L.front();
                         if (Q[cur].fa == 0) 
                            Q[cur].pre = 0;
                         else{
                              p = Q[Q[cur].fa].pre;
                              while (p && !Q[p].pos[Q[cur].ch]) p = Q[p].pre;
                              Q[cur].pre = Q[p].pos[Q[cur].ch];
                         }
                         Q[cur].tag |= Q[Q[cur].fa].tag;
                         Q[cur].tag |= Q[Q[cur].pre].tag;
                         for (int i = 0; i < 4; i ++)
                             if (Q[cur].pos[i]) L.push(Q[cur].pos[i]);
                                else Q[cur].pos[i] = Q[Q[cur].pre].pos[i];
                         L.pop();
                   }
              }
              int Nxt(int cur, int nxt){
                   return Q[cur].pos[nxt];
              }
       }T;

string GetS(){
       char ch = getchar();
       string Ans = "";
       while (ch != '\n'){
             if (ch == 'A') Ans += '0';
             if (ch == 'G') Ans += '1';
             if (ch == 'C') Ans += '2';
             if (ch == 'T') Ans += '3';
             ch = getchar();
       }
       return Ans;
}

int Min(int x, int y){
    if (y == -1 && x != -1) return x;
    if (x == -1) return y; 
    return min(x, y);
}

void print(int x){
     for (int i = 0; i < 4; i ++) cout<<f[x][i]<<" ";
     cout<<endl;
}

int main(){
      //  freopen("in.txt", "r", stdin);
      //  freopen("out.txt", "w", stdout);
        scanf("%d\n", &N); tot = 0;
        while (N){
              T.clear();
              for (int i = 0; i < N; i ++){
                  cur = GetS();
                  T.ins(cur, 0, 0);
              }
              T.fix();
              S = GetS(); L = S.length();
              for (int i = 0; i <= L; i ++)
                  for (int j = 0; j < T.Size; j ++) f[i][j] = -1;
              f[0][0] = 0;
              for (int i = 1; i <= L; i ++){
                  Si = i - 1;
                  for (int j = 0; j < T.Size; j ++){
                      if (f[i - 1][j] == -1 || T.Q[j].tag) continue;
                      for (int k = 0; k < 4; k ++){
                          tmp = T.Nxt(j, k);
                          f[i][tmp] = Min(f[i][tmp], f[i - 1][j] + (S[Si] - '0' != k));
                      }
                  }
              }
              Ans = -1;
              for (int i = 0; i < T.Size; i ++)
                  if (!T.Q[i].tag) Ans = Min(Ans, f[L][i]);
              printf("Case %d: %d\n", ++tot, Ans);
              scanf("%d\n", &N);
        }
        //system("pause");
}
