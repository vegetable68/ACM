//intersection of segments
//POJ3449
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <string>
#include <algorithm>
#define MaxN 30
using namespace std;

struct Poi{
		double x, y;
		Poi(double _x = 0, double _y = 0):x(_x), y(_y){}
		void read(){
			char S[20]; 
			double tag;
			scanf("%s", S);
			x = 0; tag = 1.;
			int pos = 0;
			while (!isdigit(S[pos])) {if (S[pos] == '-') tag = -1.; pos ++;}
			x = S[pos] - '0'; pos ++;
			while (S[pos] != ','){
				if (isdigit(S[pos])) x = x * 10 + S[pos] - '0'; pos ++; 
			} 
			x *= tag; tag = 1.;
			pos ++; y = 0;
			if (S[pos] == '-') tag = -1.;
			while (S[pos] != ')'){
				if (S[pos] == '-') tag = -1.;
				if (isdigit(S[pos])) y = y * 10 + S[pos] - '0'; pos ++;
			}
			y *= tag;
		}
		Poi operator - (const Poi &T)const{
			return Poi(x - T.x, y - T.y);
		}
		Poi operator + (const Poi &T)const{
			return Poi(x + T.x, y + T.y);
		}
		Poi operator / (const double &T)const{
			return Poi(x / T, y / T);
		}
		Poi Rot(){
			return Poi(-y, x);
		}
	};
	
double cross(Poi a, Poi b){
	return a.x * b.y - a.y * b.x;
}

struct Polygon{
		char ID;
		int Num;
		Poi pos[MaxN];
		bool operator < (const Polygon &T)const{
			return ID < T.ID;
		}
		void readsquare(){
			Num = 4;
			pos[0].read(); pos[2].read();
			Poi tmp = (pos[2] + pos[0]) / 2.;
			pos[1] = (pos[2] - tmp).Rot() + tmp;
			pos[3] = tmp - (pos[2] - tmp).Rot();
			pos[Num] = pos[0];
		}
		void readrectangle(){
			Num = 4;
			pos[0].read(); pos[1].read(); pos[2].read();
			pos[3] = pos[2] - pos[1] + pos[0];
			pos[Num] = pos[0];
		}
		void readpolygon(int _N){
			Num = _N;
			for (int i = 0; i < Num; i ++) pos[i].read();
			pos[Num] = pos[0];
		}
		void print(){
			cout<<Num<<" ";
			for (int i = 0; i < Num; i ++) cout<<pos[i].x<<","<<pos[i].y<<" ";
			cout<<endl;
		}
	}P[MaxN];
	
char S[20];
int tot, x;
string Ans[MaxN];
const double eps = 1e-9;

int sign(double x){
	if (x > eps) return 1;
	if (x < -eps) return -1;
	return 0;
 }

bool DotOnSeg(Poi x, Poi Sa, Poi Sb){
	return sign(cross(x - Sa, x - Sb)) == 0 
			&& sign(max(Sa.x, Sb.x) - x.x) >= 0 && sign(min(Sa.x, Sb.x) - x.x) <= 0
			&& sign(max(Sa.y, Sb.y) - x.y) >= 0 && sign(min(Sa.y, Sb.y) - x.y) <= 0;
}

bool check(Poi a, Poi b, Poi c, Poi d){
	if (sign(cross(d - c, b - a)) == 0){
		return DotOnSeg(c, a, b) || DotOnSeg(d, a, b) || DotOnSeg(a, c, d) || DotOnSeg(b, c, d);
	}else{
		return (sign(cross(c - a, b - a) * cross(d - a, b - a)) <= 0) && (sign(cross(d - c, a - c) * cross(d - c, b - c)) <= 0);
	}
	return 1;
}

bool intersect(int x, int y){
	//cout<<P[x].Num<<" "<<P[y].Num<<endl;
	for (int i = 0; i < P[x].Num; i ++)
		for (int j = 0; j < P[y].Num; j ++){
			//cout<<check(P[x].pos[i], P[x].pos[i + 1], P[y].pos[j], P[y].pos[j + 1])<<endl;
			if (check(P[x].pos[i], P[x].pos[i + 1], P[y].pos[j], P[y].pos[j + 1])) return true;
		}
	return false;
}

int main(){
	scanf("%s", S);
	while (S[0] != '.'){
		tot = 0;
		while (S[0] != '-'){
			P[tot].ID = S[0];
			scanf("%s", S);
			if (S[0] == 's') P[tot].readsquare();
			if (S[0] == 'l') P[tot].readpolygon(2);
			if (S[0] == 'r') P[tot].readrectangle();
			if (S[0] == 't') P[tot].readpolygon(3);
			if (S[0] == 'p') {scanf("%d", &x); P[tot].readpolygon(x);}
			tot ++;
			//cout<<S<<endl;
			scanf("%s", S);
		}
		
		sort(P, P + tot); 
		//for (int i = 0; i < tot; i ++) P[i].print();
		for (int i = 0; i < tot; i ++) Ans[i] = "";
		for (int i = 0; i < tot; i ++)
			for (int j = 0; j < tot; j ++)
				if (i != j && intersect(i, j)) Ans[i] += P[j].ID;
		//for (int i = 0; i < tot; i ++) cout<<Ans[i]<<endl;
		for (int i = 0; i < tot; i ++){
			int L = Ans[i].length();
			if (L){
				if (L == 1) printf("%c intersects with %c\n", P[i].ID, Ans[i][0]);
				if (L == 2) printf("%c intersects with %c and %c\n", P[i].ID, Ans[i][0], Ans[i][1]);
				if (L > 2){
					printf("%c intersects with ", P[i].ID);
					for (int j = 0; j < L - 1; j ++){printf("%c, ", Ans[i][j]);}
					printf("and %c\n", Ans[i][L - 1]);
				}
			}else
				printf("%c has no intersections\n", P[i].ID);
		}
		printf("\n");
		scanf("%s", S);
		//cout<<"tag"<<endl;
		//return 0;
		//cout<<"tag"<<endl;
	}
	return 0;
}
