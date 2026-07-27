/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 505;

int n, m;
int grid[MAXN][MAXN];    // 原始矩阵
int tmp[MAXN][MAXN];     // 临时存储要旋转的子矩阵
int rotated[MAXN][MAXN]; // 旋转后的子矩阵

// 旋转子矩阵：左上角 (top,left)，边长 size，clockwise=1 表示顺时针
void rotate_square(int top, int left, int size, int clockwise) {
    // 1. 复制子矩阵到 tmp
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            tmp[i][j] = grid[top + i][left + j];

    // 2. 旋转到 rotated
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (clockwise)
                rotated[i][j] = tmp[size - 1 - j][i];     // 顺时针
            else
                rotated[i][j] = tmp[j][size - 1 - i];     // 逆时针
        }
    }

    // 3. 写回原矩阵
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            grid[top + i][left + j] = rotated[i][j];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;

    // 初始化矩阵：按行填入 1..n^2
    int val = 1;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            grid[i][j] = val++;

    // 执行 m 次旋转
    for (int t = 0; t < m; t++) {
        int x, y, r, z;
        cin >> x >> y >> r >> z;
        int size = 2 * r + 1;
        int top  = x - r - 1; // 题目坐标从 1 开始，转为 0 基
        int left = y - r - 1;
        rotate_square(top, left, size, z == 0);
    }

    // 输出
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            cout << grid[i][j] << " ";
        cout << "\n";
    }

    return 0;
}
