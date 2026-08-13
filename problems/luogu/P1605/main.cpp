/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-13 13:29
 * update_at: 2026-08-13 13:40
 */
/* P1605 迷宫 */
/* DFS 回溯：统计从起点到终点的所有简单路径数量。 */

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 15;

int n, m, t;              // 迷宫长宽与障碍数量
int sx, sy, fx, fy;       // 起点与终点坐标
int blocked[MAXN][MAXN];  // blocked[x][y] = 1 表示 (x, y) 是障碍
int vis[MAXN][MAXN];      // vis[x][y] = 1 表示 (x, y) 在当前路径上已访问
long long ans;            // 路径总数
int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};

// 从 (x, y) 出发 DFS，每到达一次终点就找到一条完整路径。
void dfs(int x, int y) {
    if (x == fx && y == fy) {  // 到达终点，统计当前这条路径
        ans++;
        return;
    }

    // 这一层递归枚举四个方向的选择。
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx < 1 || nx > n || ny < 1 || ny > m) continue;  // 出界
        if (blocked[nx][ny] || vis[nx][ny]) continue;        // 障碍或已访问

        vis[nx][ny] = 1;  // 前进阶段：标记进入
        dfs(nx, ny);
        vis[nx][ny] = 0;  // 回溯阶段：撤销标记
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> t;
    cin >> sx >> sy >> fx >> fy;

    for (int i = 1; i <= t; i++) {
        int x, y;
        cin >> x >> y;
        blocked[x][y] = 1;
    }

    vis[sx][sy] = 1;  // 起点视为已访问，防止路径绕回起点
    dfs(sx, sy);
    cout << ans << '\n';
    return 0;
}
