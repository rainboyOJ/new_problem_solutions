/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-23 16:38
 * update_at: 2026-10-23 16:38
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
// brute.cpp：小数据暴力解，用 BFS 在「网格位置 + 本行已覆盖左右端点」的状态图上搜最短路。
// 不做任何结构性假设（不比 main.cpp 少搜任何一种走法），所以能真正检验 main 的正确性。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 12;  // 暴力只处理小数据：状态数 = n * n * 4，BFS 规模 n^2

int n;
int L[MAXN], R[MAXN];

// dist[row][col][mask]：到达 (row, col) 且第 row 行的覆盖情况为 mask 时的最少步数
// mask 的第 1 位表示左端点 L[row] 已走过，第 2 位表示右端点 R[row] 已走过
int dist[MAXN][MAXN][4];
bool visited[MAXN][MAXN][4];

// 计算站在 (row, col) 时本行的覆盖情况
int mask_at(int row, int col) {
    int mask = 0;
    if (col == L[row]) {
        mask |= 1;
    }
    if (col == R[row]) {
        mask |= 2;
    }
    // 左端点必须被真正“踩过”，L == R 时一个位置同时代表两端
    return mask;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> L[i] >> R[i];
    }

    memset(visited, 0, sizeof(visited));
    memset(dist, 0x3f, sizeof(dist));

    queue<int> q_row, q_col, q_mask;
    // 起点 (1,1)
    int start_mask = mask_at(1, 1);
    dist[1][1][start_mask] = 0;
    visited[1][1][start_mask] = true;
    q_row.push(1);
    q_col.push(1);
    q_mask.push(start_mask);

    int answer = 1 << 30;

    while (!q_row.empty()) {
        int row = q_row.front(); q_row.pop();
        int col = q_col.front(); q_col.pop();
        int mask = q_mask.front(); q_mask.pop();
        int d = dist[row][col][mask];

        // 到达 (n,n) 且最后一行已覆盖完，就是一个合法终点
        if (row == n && col == n && mask == 3) {
            answer = min(answer, d);
        }

        // 三种移动之一：向左
        if (col - 1 >= 1) {
            int ncol = col - 1;
            int nmask = mask | mask_at(row, ncol);
            if (!visited[row][ncol][nmask]) {
                visited[row][ncol][nmask] = true;
                dist[row][ncol][nmask] = d + 1;
                q_row.push(row); q_col.push(ncol); q_mask.push(nmask);
            }
        }

        // 向右
        if (col + 1 <= n) {
            int ncol = col + 1;
            int nmask = mask | mask_at(row, ncol);
            if (!visited[row][ncol][nmask]) {
                visited[row][ncol][nmask] = true;
                dist[row][ncol][nmask] = d + 1;
                q_row.push(row); q_col.push(ncol); q_mask.push(nmask);
            }
        }

        // 向下：只有本行线段走完了才允许
        if (row + 1 <= n && mask == 3) {
            int nrow = row + 1;
            int nmask = mask_at(nrow, col);
            if (!visited[nrow][col][nmask]) {
                visited[nrow][col][nmask] = true;
                dist[nrow][col][nmask] = d + 1;
                q_row.push(nrow); q_col.push(col); q_mask.push(nmask);
            }
        }
    }

    cout << answer << "\n";

    return 0;
}
