/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */

#include <bits/stdc++.h>
using namespace std;

int a[40][40]; // 幻方矩阵
int n;

int main() {
    cin >> n;
    int row = 1, col = (n + 1) / 2; // 第一行中间放 1
    for (int v = 1; v <= n * n; v++) {
        a[row][col] = v;
        // 计算右上方坐标（取模实现循环）
        int nr = (row - 1 + n - 1) % n + 1; // 行 -1，循环到最下面
        int nc = col % n + 1;               // 列 +1，循环到最左边
        if (a[nr][nc] != 0) {               // 右上方已被占用
            row++;                          // 放到正下方
        } else {
            row = nr;
            col = nc;
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++)
            cout << a[i][j] << " ";
        cout << "\n";
    }
    return 0;
}
