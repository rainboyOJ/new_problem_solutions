/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2025-11-28 15:41
 * update_at: 2025-11-28 15:41
 */
/*
 * 题目：[USACO08FEB] Meteor Shower S (luogu 2895)
 * 核心思路：
 * 1. 先处理所有流星，计算出每个格子最早被摧毁的时间 danger_time。
 * 2. BFS 从 (0,0) 出发，每次移动到达格子 (nx,ny) 的时间为 t+1。
 * 3. 只有 t+1 < danger_time[nx][ny] 才能进入该格子（严格小于，因为摧毁时刻即不可站）。
 * 4. 第一次到达 danger_time 为无穷的格子就是安全点，直接返回时间。
 * 5. 若队列为空还没找到，返回 -1。
 */

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000; // 流星坐标最大 300，安全边界取 1000 确保能绕行
const int INF = 0x3f3f3f3f;

int danger_time[MAXN][MAXN]; // 每个格子最早被摧毁的时间，INF 表示永不摧毁
int dist[MAXN][MAXN];        // BFS 到达时间，-1 表示未访问

// 移动方向：不动、右、左、上、下（不动用于处理流星影响的 5 个格子）
int dx[5] = {0, 1, -1, 0, 0};
int dy[5] = {0, 0, 0, 1, -1};

struct Point {
    int x, y;
};

bool in_board(int x, int y) {
    return x >= 0 && x < MAXN && y >= 0 && y < MAXN;
}

int bfs() {
    // 起点在时间 0 就被摧毁，无法出发
    if (danger_time[0][0] == 0)
        return -1;

    memset(dist, -1, sizeof(dist));
    queue<Point> q;
    dist[0][0] = 0;
    q.push({0, 0});

    while (!q.empty()) {
        Point u = q.front(); q.pop();
        int t = dist[u.x][u.y];

        // 当前格子永不摧毁，已到达安全点
        if (danger_time[u.x][u.y] == INF)
            return t;

        for (int i = 1; i <= 4; i++) {
            int nx = u.x + dx[i];
            int ny = u.y + dy[i];
            int nt = t + 1;

            if (!in_board(nx, ny)) continue;
            if (dist[nx][ny] != -1) continue;
            if (nt >= danger_time[nx][ny]) continue;

            dist[nx][ny] = nt;
            q.push({nx, ny});
        }
    }

    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 初始化 danger_time 为 INF
    for (int i = 0; i < MAXN; i++)
        for (int j = 0; j < MAXN; j++)
            danger_time[i][j] = INF;

    int m;
    cin >> m;
    for (int i = 1; i <= m; i++) {
        int x, y, t;
        cin >> x >> y >> t;
        // 每颗流星摧毁自身及上下左右共 5 个格子
        for (int k = 0; k < 5; k++) {
            int nx = x + dx[k];
            int ny = y + dy[k];
            if (!in_board(nx, ny)) continue;
            danger_time[nx][ny] = min(danger_time[nx][ny], t);
        }
    }

    cout << bfs() << '\n';
    return 0;
}
