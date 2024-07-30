#include <iostream>

using namespace std;

int fun(int m,int  n); //宣告函數

int main()
{
	int n, m; //設置函數
	cin >> m >> n; //兩個輸入
	cout<<fun(m, n);//輸出函數
}
//阿克曼函數
int fun(int m, int n) {
	if (m == 0) return n = n + 1;  
	else if (n == 0) return fun(m - 1, 1);
	else return fun(m - 1, fun(m, n - 1));
}