/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-13 13:22
 * update_at: 2026-08-13 13:22
 */
/*
 * 题目：[USACO08FEB] Meteor Shower S（洛谷 P2895）
 * 核心思路：
 * 1. 每颗流星在时间 t 摧毁 (x,y) 及上下左右四个相邻格子，
 *    预处理出每个格子最早的摧毁时间 danger。
 * 2. 从 (0,0) 做 BFS，走到新格子 (nx,ny) 的到达时间为 t+1，
 *    只有 t+1 < danger[nx][ny] 才能进入（严格小于，摧毁时刻即不可站）。
 * 3. 第一次到达永远不会被摧毁的格子（danger 为 INF）就是答案；
 *    队列耗尽还没找到则输出 -1。
 */

#include <bits/stdc++.h>
using namespace std;

// 流星坐标最大 300，受影响格子最大到 301，开 0..304 保证能逃出危险区
const int MAXN = 305;
const int INF = 0x3f3f3f3f;

int danger[MAXN][MAXN]; // danger[x][y]：格子 (x,y) 最早被摧毁的时间，INF 表示永远安全
bool vis[MAXN][MAXN];   // BFS 访问标记

int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};

struct Node {
    int x, y, t; // 当前位置与到达时间
};

int bfs() {
    // 起点在时间 0 就被摧毁，一开始就无路可走
    if (danger[0][0] == 0)
        return -1;

    memset(vis, 0, sizeof(vis));
    queue<Node> q;
    q.push({0, 0, 0});
    vis[0][0] = true;

    while (!q.empty()) {
        Node u = q.front();
        q.pop();

        // 到达了永远不会被摧毁的格子：BFS 按时间递增扩展，第一次到达即最早
        if (danger[u.x][u.y] == INF)
            return u.t;

        for (int i = 0; i < 4; i++) {
            int nx = u.x + dx[i];
            int ny = u.y + dy[i];
            if (nx < 0 || nx >= MAXN || ny < 0 || ny >= MAXN)
                continue;
            if (vis[nx][ny])
                continue;
            if (u.t + 1 >= danger[nx][ny]) // 到达时间必须严格早于摧毁时间
                continue;
            vis[nx][ny] = true;
            q.push({nx, ny, u.t + 1});
        }
    }

    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 初始化所有格子为永不摧毁
    for (int i = 0; i < MAXN; i++)
        for (int j = 0; j < MAXN; j++)
            danger[i][j] = INF;

    int m;
    cin >> m;
    for (int i = 1; i <= m; i++) {
        int x, y, t;
        cin >> x >> y >> t;
        // 流星摧毁自己与四邻格，取所有流星中最早的摧毁时间
        danger[x][y] = min(danger[x][y], t);
        if (x + 1 < MAXN) danger[x + 1][y] = min(danger[x + 1][y], t);
        if (x - 1 >= 0) danger[x - 1][y] = min(danger[x - 1][y], t);
        if (y + 1 < MAXN) danger[x][y + 1] = min(danger[x][y + 1], t);
        if (y - 1 >= 0) danger[x][y - 1] = min(danger[x][y - 1], t);
    }

    cout << bfs() << '\n';
    return 0;
}
