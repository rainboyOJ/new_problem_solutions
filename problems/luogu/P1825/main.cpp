/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-13 13:33
 * update_at: 2026-08-13 13:35
 */
// main.cpp：P1825 Corn Maze S 正式解。BFS 求最短路，
// 走入传送门端点时在展开邻居的同一层内立即瞬移到配对端点。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 305;
const int MAXM = 305;

int n, m;
char maze[MAXN][MAXM];      // 迷宫，maze[i][j] 是 (i,j) 上的字符
int dist[MAXN][MAXM];       // dist[i][j] 起点到 (i,j) 的最少步数，-1 表示未访问

int sx, sy;                 // 起点 @ 的坐标
int ex, ey;                 // 终点 = 的坐标

int to_x[MAXN][MAXM];       // (i,j) 是传送门端点时，配对端点的横坐标，否则为 -1
int to_y[MAXN][MAXM];       // 配对端点的纵坐标

int cnt[26];                // cnt[c] 大写字母 c 出现的次数（每个字母恰好 2 次）
int px[26][2], py[26][2];   // 每个大写字母两个端点的坐标

int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};

// 判断 (x,y) 是否在迷宫范围内
bool in_maze(int x, int y) {
    return x >= 1 && x <= n && y >= 1 && y <= m;
}

void read_input() {
    cin >> n >> m;
    memset(to_x, -1, sizeof(to_x));
    memset(to_y, -1, sizeof(to_y));

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

    // 每个字母恰好两个端点，把它们互相记录为对方的配对端点
    for (int c = 0; c < 26; c++) {
        if (cnt[c] == 2) {
            int x1 = px[c][0], y1 = py[c][0];
            int x2 = px[c][1], y2 = py[c][1];
            to_x[x1][y1] = x2;
            to_y[x1][y1] = y2;
            to_x[x2][y2] = x1;
            to_y[x2][y2] = y1;
        }
    }
}

// BFS 求最短步数：移动一格计 1 步；走入传送门端点必须瞬移，瞬移免费，
// 所以"走一步 + 瞬移"整体仍只计 1 步。
int bfs() {
    queue<pair<int, int>> q;
    memset(dist, -1, sizeof(dist));

    dist[sx][sy] = 0;
    q.push(make_pair(sx, sy));

    while (!q.empty()) {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();

        if (x == ex && y == ey) {
            return dist[x][y];
        }

        for (int k = 0; k < 4; k++) {
            int nx = x + dx[k];
            int ny = y + dy[k];

            if (!in_maze(nx, ny) || maze[nx][ny] == '#') continue;

            // 走入的是传送门端点：必须瞬移到配对端点。
            // 配对端点与当前端点同字母，瞬移恰好一次即完成；
            // 若瞬移后再次检查传送门，就会在两个端点之间来回跳，形成死循环。
            if (to_x[nx][ny] != -1) {
                // 先保存配对端点坐标再赋值，避免修改 nx 后 to_y 下标错位
                int tx = to_x[nx][ny];
                int ty = to_y[nx][ny];
                nx = tx;
                ny = ty;
            }

            if (dist[nx][ny] == -1) {
                dist[nx][ny] = dist[x][y] + 1;
                q.push(make_pair(nx, ny));
            }
        }
    }
    return -1; // 终点不可达
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    cout << bfs() << '\n';

    return 0;
}
