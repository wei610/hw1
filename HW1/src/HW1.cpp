#include <iostream>

using namespace std;

int fun(int m, int n); // 宣告函數

int main()
{
    int n, m; // 設置變數
    cin >> m >> n; // 輸入兩個值
    cout << fun(m, n); // 輸出結果
}

// 阿克曼函數變為無限迴圈
int fun(int m, int n) {
    while (true) {
        if (m == 0) {
            n = n + 1;
            break; // 跳出無限迴圈
        }
        else if (n == 0) {
            m = m - 1;
            n = 1;
        }
        else {
            n = fun(m, n - 1);
            m = m - 1;
        }
    }
    return n;
}
