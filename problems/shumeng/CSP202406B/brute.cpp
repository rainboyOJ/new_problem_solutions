/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 22:39
 */
// brute.cpp：小数据暴力解，直接维护二维矩阵完成重塑、转置与查询。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10005;

int matrix[MAXN][MAXN]; // 直接保存二维矩阵
int n, m;

// 重塑为 x 行 y 列：先按行优先取出所有元素，再按新形状放回
void reshape(int x, int y) {
    int temp[MAXN];
    int count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) temp[count++] = matrix[i][j];
    }
    count = 0;
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) matrix[i][j] = temp[count++];
    }
    n = x;
    m = y;
}

// 转置：新矩阵的 (j,i) 位置放原矩阵的 (i,j)
void transpose() {
    int temp[MAXN]; // 平铺存放转置后的元素
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            temp[j * n + i] = matrix[i][j];
        }
    }
    int count = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) matrix[i][j] = temp[count++];
    }
    swap(n, m);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int operation_count;
    cin >> n >> m >> operation_count;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) cin >> matrix[i][j];
    }

    while (operation_count--) {
        int type, x, y;
        cin >> type >> x >> y;
        if (type == 1) {
            reshape(x, y);
        } else if (type == 2) {
            transpose();
        } else {
            cout << matrix[x][y] << '\n';
        }
    }

    return 0;
}