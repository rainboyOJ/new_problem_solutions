/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */

#include <bits/stdc++.h>
using namespace std;

int a[25][25]; // a[row][col] 存储杨辉三角
int n;

int main() {
    cin >> n;
    for (int r = 1; r <= n; r++) {
        a[r][1] = 1;       // 第一列始终为 1
        a[r][r] = 1;       // 对角线始终为 1
        // 中间元素等于上一行相邻两个数之和
        for (int c = 2; c < r; c++) {
            a[r][c] = a[r - 1][c - 1] + a[r - 1][c];
        }
    }
    for (int r = 1; r <= n; r++) {
        for (int c = 1; c <= r; c++)
            cout << a[r][c] << " ";
        cout << "\n";
    }
    return 0;
}
