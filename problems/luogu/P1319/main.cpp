/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */

#include <bits/stdc++.h>
using namespace std;

char grid[205][205]; // 还原后的 01 矩阵
int n;

int main() {
    cin >> n;
    int len;          // 游程长度
    char cur = '0';   // 当前要填充的字符，从 0 开始
    int x = 1, y = 1; // 当前填充位置

    while (cin >> len) {
        // 将 cur 重复 len 次填入矩阵
        for (int k = 1; k <= len; k++) {
            grid[x][y] = cur;
            y++;
            if (y > n) { // 换行
                y = 1;
                x++;
            }
        }
        // 切换填充字符（0 <-> 1）
        cur = (cur == '0') ? '1' : '0';
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++)
            cout << grid[i][j];
        cout << "\n";
    }
    return 0;
}
