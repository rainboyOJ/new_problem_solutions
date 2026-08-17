/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 22:39
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10005;

int value[MAXN]; // 行优先保存的矩阵元素
int n, m;        // 当前矩阵的行数与列数

// 矩阵转置：原位置 (i,j) 的线性下标 i*m+j，转置后位置 (j,i) 的线性下标 j*n+i
void transpose() {
    int temp[MAXN];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            temp[j * n + i] = value[i * m + j];
        }
    }
    for (int i = 0; i < n * m; i++) value[i] = temp[i];
    swap(n, m);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int operation_count;
    cin >> n >> m >> operation_count;
    for (int i = 0; i < n * m; i++) cin >> value[i];

    while (operation_count--) {
        int type, x, y;
        cin >> type >> x >> y;
        if (type == 1) {
            n = x; // 重塑：只改形状，行优先序列不变
            m = y;
        } else if (type == 2) {
            transpose(); // 转置：需要重排元素并交换行列
        } else {
            cout << value[x * m + y] << '\n';
        }
    }

    return 0;
}