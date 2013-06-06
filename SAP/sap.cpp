/*
PROG:ditch
LANG:C++
SAP
*/
#include<iostream>
#include<fstream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cctype>
#include<cmath>
#include<string>
#include<algorithm>
#include<functional>
#include<bitset>
#include<deque>
#include<queue>
#include<stack>
#include<vector>
#include<set>
#include<map>
#include<complex>
#include<cstdarg>
#include<cerrno>
#include<cstddef>
#include<csetjmp>
#include<cfloat>
#include<ciso646>
#include<climits>
#include<clocale>
#include<ctime>
#include<cassert>
#include<csignal>
#include<exception>
#include<ios>
#include<iomanip>
#include<istream>
#include<iterator>
#include<iosfwd>
#include<list>
#include<locale>
#include<limits>
#include<memory>
#include<new>
#include<numeric>
#include<ostream>
#include<sstream>
#include<stdexcept>
#include<streambuf>
#include<typeinfo>
#include<utility>
#include<valarray>
using namespace std;
const int MaxN=10005;
const int MaxE=300005;
int Next[MaxE],Node[MaxE],C[MaxE],Lnk[MaxN],h[MaxN],Gap[MaxN];
int cnt=-1,n,m,flow,x,y,l,s=1;
int aug(int cur,int CurFlow){
   if (cur==n){
      flow+=CurFlow;
      return CurFlow;
   }
   int Temp,MinH=n-1;
   for (int i=Lnk[cur];i!=-1;i=Next[i])
     if (C[i]>0){
        if (h[Node[i]]+1==h[cur])
           if (Temp=aug(Node[i],min(CurFlow,C[i]))){
	          C[i]-=Temp;
	          C[i^1]+=Temp;
	          return Temp;
	       }
        MinH=min(MinH,h[Node[i]]);
     }
   Gap[h[cur]]--;
   if (Gap[h[cur]]==0) h[s]=n;
   h[cur]=MinH+1;
   Gap[h[cur]]++;
   return 0;
}
void Insert(int x,int y,int l){
   C[++cnt]=l;
   Node[cnt]=y;
   Next[cnt]=Lnk[x];
   Lnk[x]=cnt;
}
int main(){
//    freopen("ditch.in","r",stdin);
//    freopen("ditch.out","w",stdout);
    scanf("%d%d",&m,&n);
    memset(Lnk,-1,sizeof(Lnk));
    for (int i=1;i<=m;i++){
       scanf("%d%d%d",&x,&y,&l);
       Insert(x,y,l);
       Insert(y,x,0);
    }
    Gap[0]=n;
    while (h[s]<n)aug(s,0x3FFFFFFF);
    printf("%d\n",flow);
//    system("pause");
    return 0;
}
