/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2025-11-28 15:41
 * update_at: 2025-11-28 15:41
 */
/*
 * 题目：[CSP-J 2020] 方格取数 (luogu 7074)
 * 核心思路：
 * 1. 不能向左，按列从左往右 DP，定义 f[i][j] = 走到 (i,j) 的最大和。
 * 2. 同一列内方向只能单调，否则会重复走格子。
 * 3. 每列做两次 O(n) 扫描：
 *    - down[i]：从上往下走到第 i 行的最优值
 *    - up[i]：从下往上走到第 i 行的最优值
 * 4. 取两者较大值存入 f[i][j]。
 */

#include <bits/stdc++.h>
using namespace std;

// ===== 输入数据 =====
const int MAXN = 1005;
int n, m;
int a[MAXN][MAXN];

// ===== DP 数组 =====
long long f[MAXN][MAXN];    // f[i][j] = 走到 (i,j) 的最大和
long long down[MAXN][MAXN]; // down[i][j] = 第 j 列从上往下到 i 行的最优值
long long up[MAXN][MAXN];   // up[i][j] = 第 j 列从下往上到 i 行的最优值

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cin >> a[i][j];

    // 第一列：从 (1,1) 出发只能往下走
    down[1][1] = a[1][1];
    up[1][1] = a[1][1];
    f[1][1] = a[1][1];
    for (int i = 2; i <= n; i++) {
        down[i][1] = down[i - 1][1] + a[i][1];
        up[i][1] = down[i][1]; // 第一列没有向上走的机会
        f[i][1] = down[i][1];
    }

    // 第 2 列到第 m 列
    for (int j = 2; j <= m; j++) {
        // 从上往下扫描
        down[1][j] = f[1][j - 1] + a[1][j];
        for (int i = 2; i <= n; i++)
            down[i][j] = max(f[i][j - 1], down[i - 1][j]) + a[i][j];

        // 从下往上扫描
        up[n][j] = f[n][j - 1] + a[n][j];
        for (int i = n - 1; i >= 1; i--)
            up[i][j] = max(f[i][j - 1], up[i + 1][j]) + a[i][j];

        // 合并
        for (int i = 1; i <= n; i++)
            f[i][j] = max(down[i][j], up[i][j]);
    }

    cout << f[n][m] << '\n';
    return 0;
}
