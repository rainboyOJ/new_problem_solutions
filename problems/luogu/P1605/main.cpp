/**
 * Author by Rainboy blog: https://rainboylv.com github: https://rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */

/* P1605 迷宫 */
/* DFS 回溯统计从起点到终点的所有简单路径数量。 */

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10;

int n, m, obs_cnt;
int sx, sy, fx, fy; // 起点和终点
int vis[MAXN][MAXN]; // 0 可走，1 障碍物或已访问
int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};
int ans;

// 从 (x,y) 出发 DFS 统计路径数
void dfs(int x, int y) {
    if (x == fx && y == fy) {
        ans++;
        return;
    }

    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx < 1 || nx > n || ny < 1 || ny > m) continue;
        if (vis[nx][ny]) continue;

        vis[nx][ny] = 1;  // 标记已访问
        dfs(nx, ny);
        vis[nx][ny] = 0;  // 回溯撤销
    }
}

int main() {
    cin >> n >> m >> obs_cnt;
    cin >> sx >> sy >> fx >> fy;

    for (int i = 1; i <= obs_cnt; i++) {
        int x, y;
        cin >> x >> y;
        vis[x][y] = 1; // 障碍物
    }

    vis[sx][sy] = 1; // 起点标记
    dfs(sx, sy);
    cout << ans << "\n";
    return 0;
}
