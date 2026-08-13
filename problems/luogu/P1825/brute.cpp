/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-13 13:33
 * update_at: 2026-08-13 13:33
 */
// brute.cpp：小数据暴力解。把每个格子看成一个点，把每个合法移动建成一条
// 代价为 1 的有向边（走入传送门端点时直接连到配对端点），在显式图上跑普通 BFS。
// 与 main.cpp"展开邻居时内联瞬移"的写法相互独立，用来辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 305;
const int MAXV = 305 * 305 + 5;

int n, m;
char maze[MAXN][MAXN];      // 迷宫
int sx, sy, ex, ey;         // 起点 @ 与终点 =

int cnt[26];                // 每个大写字母出现的次数
int px[26][2], py[26][2];   // 每个大写字母两个端点的坐标

int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};

vector<int> g[MAXV];        // 显式图：g[id] 存放从该点走一步能到达的点
int dist[MAXV];             // dist[id] 起点到该点的最少步数，-1 表示未访问

// 把坐标 (x,y) 映射成图上的点编号
int id(int x, int y) {
    return x * m + y;
}

// 读入迷宫，记录起点、终点和传送门端点
void read_input() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> (maze[i] + 1);
        for (int j = 1; j <= m; j++) {
            if (maze[i][j] == '@') {
                sx = i;
                sy = j;
            } else if (maze[i][j] == '=') {
                ex = i;
                ey = j;
            } else if (maze[i][j] >= 'A' && maze[i][j] <= 'Z') {
                int c = maze[i][j] - 'A';
                px[c][cnt[c]] = i;
                py[c][cnt[c]] = j;
                cnt[c]++;
            }
        }
    }
}

// 显式建图：从每个格子向"走一步能到达的格子"连一条 1 权边
void build_graph() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (maze[i][j] == '#') continue;

            for (int k = 0; k < 4; k++) {
                int nx = i + dx[k];
                int ny = j + dy[k];

                if (nx < 1 || nx > n || ny < 1 || ny > m) continue;
                if (maze[nx][ny] == '#') continue;

                if (maze[nx][ny] >= 'A' && maze[nx][ny] <= 'Z') {
                    // 走入传送门端点：必须瞬移到配对端点，瞬移免费，所以仍是 1 权边
                    int c = maze[nx][ny] - 'A';
                    int ox = px[c][0], oy = py[c][0];
                    if (ox == nx && oy == ny) {
                        ox = px[c][1];
                        oy = py[c][1];
                    }
                    g[id(i, j)].push_back(id(ox, oy));
                } else {
                    g[id(i, j)].push_back(id(nx, ny));
                }
            }
        }
    }
}

// 普通 BFS 求最短路
int bfs() {
    queue<int> q;
    memset(dist, -1, sizeof(dist));

    int s = id(sx, sy);
    int t = id(ex, ey);
    dist[s] = 0;
    q.push(s);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        if (u == t) {
            return dist[u];
        }

        for (size_t i = 0; i < g[u].size(); i++) {
            int v = g[u][i];
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
    return -1; // 终点不可达
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    build_graph();
    cout << bfs() << '\n';

    return 0;
}
