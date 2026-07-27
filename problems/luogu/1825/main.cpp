/**
 * Author by Rainboy blog: https://rainboylv.com github: https://rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */

/* P1825 [USACO11OPEN] Corn Maze S */
/* BFS 迷宫最短路，踏入传送门立即跳转到另一端。 */

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 305;

int n, m;
char g[MAXN][MAXN];        // 迷宫
int sx, sy;                // 起点
int tx[MAXN][MAXN];        // 传送门另一端 x
int ty[MAXN][MAXN];        // 传送门另一端 y
int vis[MAXN][MAXN];       // 最短步数
int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};

int main() {
    cin >> n >> m;
    // 读取迷宫并记录传送门两端
    int portal_x[26][2], portal_y[26][2];
    int portal_cnt[26] = {0};

    for (int i = 1; i <= n; i++) {
        cin >> (g[i] + 1);
        for (int j = 1; j <= m; j++) {
            if (g[i][j] == '@') {
                sx = i, sy = j;
            } else if (g[i][j] >= 'A' && g[i][j] <= 'Z') {
                int idx = g[i][j] - 'A';
                portal_x[idx][portal_cnt[idx]] = i;
                portal_y[idx][portal_cnt[idx]] = j;
                portal_cnt[idx]++;
            }
        }
    }

    // 建立传送门端到端的映射
    for (int c = 0; c < 26; c++) {
        if (portal_cnt[c] == 2) {
            int x1 = portal_x[c][0], y1 = portal_y[c][0];
            int x2 = portal_x[c][1], y2 = portal_y[c][1];
            tx[x1][y1] = x2, ty[x1][y1] = y2;
            tx[x2][y2] = x1, ty[x2][y2] = y1;
        }
    }

    // BFS
    queue<pair<int, int>> q;
    memset(vis, -1, sizeof(vis));
    q.push({sx, sy});
    vis[sx][sy] = 0;

    while (!q.empty()) {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();

        if (g[x][y] == '=') {
            cout << vis[x][y] << "\n";
            return 0;
        }

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx < 1 || nx > n || ny < 1 || ny > m) continue;
            if (g[nx][ny] == '#') continue;

            // 如果是传送门，跳转到另一端
            if (tx[nx][ny]) {
                int nnx = tx[nx][ny];
                int nny = ty[nx][ny];
                nx = nnx, ny = nny;
            }

            if (vis[nx][ny] != -1) continue;
            vis[nx][ny] = vis[x][y] + 1;
            q.push({nx, ny});
        }
    }

    return 0;
}
