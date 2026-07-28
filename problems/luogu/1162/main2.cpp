/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-28 17:27
 * update_at: 2026-07-28 17:27
 */
// main2.cpp：两次 BFS。第一次判断 0 区域能否走到边界，第二次把内部闭合圈填为 2。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 35;

int n;
int g[MAXN][MAXN];    // 0: 未访问, 1: 墙, 2: 内部填涂
bool vis[MAXN][MAXN]; // BFS1 专用访问标记
int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};

// BFS1：从 (sx,sy) 出发探索整个 0 区域，不修改 g。
// 判断该区域能否走到矩阵边界（能不能走出去）。
// 返回 true 表示能走出去（外部区域），false 表示被包围（内部区域）。
bool bfs1(int sx, int sy) {
    if (g[sx][sy] != 0 || vis[sx][sy])
        return false;

    bool can_get_out = false;
    queue<pair<int,int>> q;
    q.push({sx, sy});
    vis[sx][sy] = true;

    while (!q.empty()) {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();

        // 当前格子位于矩阵边界，说明可以走出去
        if (x == 1 || x == n || y == 1 || y == n)
            can_get_out = true;

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx < 1 || nx > n || ny < 1 || ny > n)
                continue;
            if (vis[nx][ny] || g[nx][ny] != 0)
                continue;
            vis[nx][ny] = true;
            q.push({nx, ny});
        }
    }
    return can_get_out;
}

// BFS2：从 (sx,sy) 出发 flood fill，把整个内部闭合圈改为 2
void bfs2(int sx, int sy) {
    queue<pair<int,int>> q;
    q.push({sx, sy});
    g[sx][sy] = 2;

    while (!q.empty()) {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx < 1 || nx > n || ny < 1 || ny > n)
                continue;
            if (g[nx][ny] != 0)
                continue;
            g[nx][ny] = 2;
            q.push({nx, ny});
        }
    }
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
            if (g[i][j] == 0 && !vis[i][j]) {
                // BFS1：判断这个 0 区域能不能走出去
                if (!bfs1(i, j)) {
                    // 不能走出去 → 内部闭合圈，BFS2 填涂为 2
                    bfs2(i, j);
                }
                // 能走出去 → 外部区域，不做处理（保留 0）
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (g[i][j] == 1)
                cout << 1 << " ";
            else if (g[i][j] == 2)
                cout << 2 << " ";
            else
                cout << 0 << " ";
        }
        cout << "\n";
    }
    return 0;
}
