/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-13 13:30
 * update_at: 2026-08-13 13:31
 */
// brute.cpp：小数据暴力解，直接按题意对每个 0 判断能否走到矩阵边界，用来理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 35;

int n;
int g[MAXN][MAXN];    // 原矩阵
bool vis[MAXN][MAXN]; // 每次判断独立使用，标记本轮访问过的 0
int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};

// 从 (sx,sy) 出发只走 0，看能否到达矩阵边界。
// 用一个新 BFS 搜索整个连通区域：只要区域内出现边界格子就能走出去。
bool can_escape(int sx, int sy) {
    memset(vis, 0, sizeof(vis));

    queue<pair<int, int>> q;
    q.push({sx, sy});
    vis[sx][sy] = true;

    while (!q.empty()) {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();

        // 当前格子在矩阵边界上：说明从这个 0 可以走到边界。
        if (x == 1 || x == n || y == 1 || y == n) {
            return true;
        }

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx < 1 || nx > n || ny < 1 || ny > n) continue;
            if (vis[nx][ny] || g[nx][ny] == 1) continue;
            vis[nx][ny] = true;
            q.push({nx, ny});
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> g[i][j];
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            // 每个 0 独立判断一次：走不出去就是闭合圈内部，填 2。
            if (g[i][j] == 0 && !can_escape(i, j)) {
                g[i][j] = 2;
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cout << g[i][j];
            if (j < n) cout << " ";
        }
        cout << "\n";
    }
    return 0;
}
