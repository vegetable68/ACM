//hash of strings
//POJ2532
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <string>
#define ULL unsigned long long
#define base1 37
#define base2 1000000007
using namespace std;

int Month[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
string Name[13] = {"", "JANUARY", "FEBRUARY", "MARCH", "APRIL", "MAY", "JUNE", "JULY", "AUGUST", "SEPTEMBER", "OCTOBER", "NOVEMBER", "DECEMBER"};
int N, M, Day, Sum, Ini_x, Ini_y, Cur_x, Cur_y, nxt;
string S[15];
bool tag, flag;
char C[100][100];
ULL H, cur, h[100][100], P_base1, P_base2, Fh[100][100];

int digit(char x){
	if (x == '.') return 0;
	if (x >= '0' && x <= '9') return x - '0' + 1;
	return x - 'A' + 11;
}

int main(){
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
	scanf("%d %d\n", &M, &N);
	H = 0; 
	P_base1 = 1; for (int i = 1; i < M; i ++) P_base1 *= base1;
	P_base2 = 1; for (int i = 1; i < N; i ++) P_base2 *= base2;
	for (int i = 0; i < N; i ++){
		cin>>S[i]; cur = 0;
		for (int j = 0; j < M; j ++)
			cur = cur * base1 + digit(S[i][j]);
		H = H * base2 + cur;
		//cout<<S[i]<<endl;
	}
	//cout<<H<<endl;
	Sum = 0; Day = 0; flag = 0;
	for (int year = 1900; year <= 2100; year ++){
		for (int i = 1; i <= 73; i ++) for (int j = 1; j <= 28; j ++) C[j][i] = '.';
		if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) Month[2] = 29; else Month[2] = 28;
		Ini_x = 1; Ini_y = 1;
		for (int i = 1; i <= 12; i ++){
			if (i % 4 == 1 && i != 1){
				Ini_x += 9; Ini_y = 1;
			}
			if (i % 4 != 1) Ini_y += 18;
			for (int j = 0; j < Name[i].length(); j ++)
				C[1 + Ini_x][j + 2 + Ini_y] = Name[i][j];
			Cur_y = Ini_y + 1;
			for (int j = 1; j <= Month[i]; j ++){
				Day ++; nxt = 0;
				Day %= 7; if (Day == 0) {Day = 7; nxt = 3;}
				Cur_x = Day + 1 + Ini_x;
				C[Cur_x][Cur_y + 1] = char(j % 10 + '0');
				if (j >= 10) C[Cur_x][Cur_y] = char(j / 10 + '0');
				Cur_y += nxt;
			}
 		}
		//cout<<"tag"<<endl;
		/*for (int i = 1; i <= 28; i ++){
			for (int j = 1; j <= 73; j ++) cout<<C[i][j];
			cout<<endl;
		}
		cout<<endl;*/
		tag = 0;
		for (int i = 1; i <= 28; i ++){
			h[i][0] = 0;
			for (int j = 1; j <= M; j ++) h[i][j] = h[i][j - 1] * base1 + digit(C[i][j]);
			for (int j = M + 1; j <= 73; j ++) h[i][j] = (h[i][j - 1] - P_base1 * digit(C[i][j - M])) * base1 + digit(C[i][j]);
		}
		for (int j = 1; j <= 73; j ++) Fh[1][j] = h[1][j];
		for (int i = 2; i <= N; i ++)
			for (int j = 1; j <= 73; j ++) Fh[i][j] = h[i][j] + Fh[i - 1][j] * base2;
		for (int i = N + 1; i <= 28; i ++)
			for (int j = 1; j <= 73; j ++) Fh[i][j] = (Fh[i - 1][j] - P_base2 * h[i - N][j]) * base2 + h[i][j];
		for (int i = N; i <= 28; i ++)
			for (int j = M; j <= 73; j ++)
				if (Fh[i][j] == H) tag = 1;
		if (tag) {flag = 1; printf("%d\n", year);}
	}
	if (!flag) printf("0\n");
}
