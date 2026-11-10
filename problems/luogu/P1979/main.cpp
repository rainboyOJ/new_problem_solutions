/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-11 00:32
 * update_at: 2026-11-11 00:32
 */
#include <algorithm>
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

const int INF = 0x3f3f3f3f;
const int dx[4] = {-1, 1, 0, 0};
const int dy[4] = {0, 0, -1, 1};

int n, m, q;
int grid[35][35];
int bfs_dis[35][35];

struct Edge {
    int to;
    int w;
};

vector<Edge> g[4000];

// 状态唯一编码：(x, y) 处在 [1, n] x [1, m]，d 在 [0, 3]
inline int get_id(int x, int y, int d) {
    return ((x - 1) * m + (y - 1)) * 4 + d;
}

// 广度优先搜索：以 (bx, by) 为障碍物，求从 (sx, sy) 出发到各格子的最短路
void bfs(int sx, int sy, int bx, int by) {
    memset(bfs_dis, 0x3f, sizeof(bfs_dis));
    if (grid[sx][sy] == 0) return;

    queue<pair<int, int>> Q;
    bfs_dis[sx][sy] = 0;
    Q.push({sx, sy});

    while (!Q.empty()) {
        auto [x, y] = Q.front();
        Q.pop();

        for (int i = 0; i < 4; ++i) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx < 1 || nx > n || ny < 1 || ny > m) continue;
            if (grid[nx][ny] == 0) continue;
            if (nx == bx && ny == by) continue; // 目标棋子所在位置不能经过

            if (bfs_dis[nx][ny] == INF) {
                bfs_dis[nx][ny] = bfs_dis[x][y] + 1;
                Q.push({nx, ny});
            }
        }
    }
}

// 静态预处理所有状态之间的转移边
void build_graph() {
    for (int x = 1; x <= n; ++x) {
        for (int y = 1; y <= m; ++y) {
            if (grid[x][y] == 0) continue;

            // 1. 棋子与空白格互换位置
            for (int d = 0; d < 4; ++d) {
                int ex = x + dx[d];
                int ey = y + dy[d];
                if (ex < 1 || ex > n || ey < 1 || ey > m || grid[ex][ey] == 0) continue;

                int u = get_id(x, y, d);
                int v = get_id(ex, ey, d ^ 1);
                g[u].push_back({v, 1});
            }

            // 2. 棋子不动，空白格绕行到棋子的其他相邻方向
            for (int d1 = 0; d1 < 4; ++d1) {
                int e1x = x + dx[d1];
                int e1y = y + dy[d1];
                if (e1x < 1 || e1x > n || e1y < 1 || e1y > m || grid[e1x][e1y] == 0) continue;

                // 以 (x, y) 为障碍物跑 BFS
                bfs(e1x, e1y, x, y);

                for (int d2 = 0; d2 < 4; ++d2) {
                    if (d1 == d2) continue;
                    int e2x = x + dx[d2];
                    int e2y = y + dy[d2];
                    if (e2x < 1 || e2x > n || e2y < 1 || e2y > m || grid[e2x][e2y] == 0) continue;

                    if (bfs_dis[e2x][e2y] != INF) {
                        int u = get_id(x, y, d1);
                        int v = get_id(x, y, d2);
                        g[u].push_back({v, bfs_dis[e2x][e2y]});
                    }
                }
            }
        }
    }
}

int dis[4000];

void solve_query() {
    int ex, ey, sx, sy, tx, ty;
    cin >> ex >> ey >> sx >> sy >> tx >> ty;

    // 起点与目标相同，直接 0 步
    if (sx == tx && sy == ty) {
        cout << 0 << "\n";
        return;
    }

    // 以棋子 (sx, sy) 为障碍物，求初始空白格 (ex, ey) 移动到棋子 4 个相邻方向的最短路
    bfs(ex, ey, sx, sy);

    memset(dis, 0x3f, sizeof(dis));
    using State = pair<int, int>;
    priority_queue<State, vector<State>, greater<State>> pq;

    for (int d = 0; d < 4; ++d) {
        int nx = sx + dx[d];
        int ny = sy + dy[d];
        if (nx < 1 || nx > n || ny < 1 || ny > m || grid[nx][ny] == 0) continue;

        if (bfs_dis[nx][ny] != INF) {
            int u = get_id(sx, sy, d);
            dis[u] = bfs_dis[nx][ny];
            pq.push({dis[u], u});
        }
    }

    // Dijkstra 求解
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if (d > dis[u]) continue;

        for (const auto& e : g[u]) {
            if (dis[u] + e.w < dis[e.to]) {
                dis[e.to] = dis[u] + e.w;
                pq.push({dis[e.to], e.to});
            }
        }
    }

    // 统计到达目标位置 (tx, ty) 的 4 个状态的最小值
    int ans = INF;
    for (int d = 0; d < 4; ++d) {
        int u = get_id(tx, ty, d);
        ans = min(ans, dis[u]);
    }

    if (ans == INF) {
        cout << -1 << "\n";
    } else {
        cout << ans << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> n >> m >> q)) return 0;

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cin >> grid[i][j];
        }
    }

    build_graph();

    while (q--) {
        solve_query();
    }

    return 0;
}
