/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-13 13:22
 * update_at: 2026-08-13 13:22
 */
// brute.cpp：小数据暴力解，把时间显式写进状态 (x,y,t)，逐秒搜索。
// 它不利用「第一次到达某个格子就是最早到达」的性质，同一个格子可能被
// 多次访问，状态数多，只适合小数据验证，用来和 main.cpp 对拍。

#include <bits/stdc++.h>
using namespace std;

const int LIM = 40;         // 小数据地图范围 0..39，远大于 gen.py 的流星影响区域
const int MAXT = LIM * LIM; // 时间上限：最短路经过的格子互不相同，长度不可能超过格点总数
const int INF = 0x3f3f3f3f;

int danger[LIM][LIM];        // 每个格子最早被摧毁的时间
bool vis[LIM][LIM][MAXT];    // 状态 (x,y,t) 是否访问过

int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};

struct Node {
    int x, y, t; // 位置与到达时间
};

int solve() {
    // 起点在时间 0 就被摧毁，一开始就无路可走
    if (danger[0][0] == 0)
        return -1;

    memset(vis, 0, sizeof(vis));
    queue<Node> q;
    q.push({0, 0, 0});
    vis[0][0][0] = true;

    while (!q.empty()) {
        Node u = q.front();
        q.pop();

        // 到达了永远不会被摧毁的格子，当前时间就是答案
        if (danger[u.x][u.y] == INF)
            return u.t;

        // 超过时间上限，认为这个分支不可能通向答案
        if (u.t + 1 >= MAXT)
            continue;

        for (int i = 0; i < 4; i++) {
            int nx = u.x + dx[i];
            int ny = u.y + dy[i];
            if (nx < 0 || nx >= LIM || ny < 0 || ny >= LIM)
                continue;
            if (u.t + 1 >= danger[nx][ny]) // 到达时间必须严格早于摧毁时间
                continue;
            if (vis[nx][ny][u.t + 1])
                continue;
            vis[nx][ny][u.t + 1] = true;
            q.push({nx, ny, u.t + 1});
        }
    }

    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 初始化所有格子为永不摧毁
    for (int i = 0; i < LIM; i++)
        for (int j = 0; j < LIM; j++)
            danger[i][j] = INF;

    int m;
    cin >> m;
    for (int i = 1; i <= m; i++) {
        int x, y, t;
        cin >> x >> y >> t;
        // 流星摧毁自己与四邻格，取所有流星中最早的摧毁时间
        danger[x][y] = min(danger[x][y], t);
        if (x + 1 < LIM) danger[x + 1][y] = min(danger[x + 1][y], t);
        if (x - 1 >= 0) danger[x - 1][y] = min(danger[x - 1][y], t);
        if (y + 1 < LIM) danger[x][y + 1] = min(danger[x][y + 1], t);
        if (y - 1 >= 0) danger[x][y - 1] = min(danger[x][y - 1], t);
    }

    cout << solve() << '\n';
    return 0;
}
