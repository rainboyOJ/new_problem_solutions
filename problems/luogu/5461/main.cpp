/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */

#include <bits/stdc++.h>
using namespace std;

int a[1030][1030]; // 赦免矩阵，1 表示未被赦免，0 表示赦免
int n;

// 递归处理左上角为 (x,y)、边长为 size 的方阵
void pardon(int x, int y, int size) {
    if (size == 1) return; // 最小单元，直接返回
    int half = size / 2;
    // 左上角 half*half 区域全部赦免（设为 0）
    for (int i = x; i < x + half; i++)
        for (int j = y; j < y + half; j++)
            a[i][j] = 0;
    // 递归处理其他三个子方阵
    pardon(x, y + half, half);       // 右上
    pardon(x + half, y, half);       // 左下
    pardon(x + half, y + half, half); // 右下
}

int main() {
    cin >> n;
    int size = 1 << n; // 2^n
    // 初始全为 1（未被赦免）
    for (int i = 1; i <= size; i++)
        for (int j = 1; j <= size; j++)
            a[i][j] = 1;
    // 从整个方阵开始递归处理
    pardon(1, 1, size);
    for (int i = 1; i <= size; i++) {
        for (int j = 1; j <= size; j++)
            cout << a[i][j] << " ";
        cout << "\n";
    }
    return 0;
}
