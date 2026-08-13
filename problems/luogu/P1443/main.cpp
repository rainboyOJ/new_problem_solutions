/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-13 13:19
 * update_at: 2026-08-13 13:20
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 405; // n, m <= 400

int n, m, sx, sy;
int dista[MAXN][MAXN];          // dista[i][j]：起点到 (i,j) 的最少步数，-1 表示未访问/不可达
int dx[8] = {-2, -2, -1, -1, 1, 1, 2, 2}; // 马的 8 种跳法
int dy[8] = {-1, 1, -2, 2, -2, 2, -1, 1};

struct Node {
    int x;
    int y;
};

// 判断格子是否在棋盘内。
bool in_board(int x, int y) {
    return x >= 1 && x <= n && y >= 1 && y <= m;
}

// 从起点做一次 BFS，求出到所有格子的最短步数。
void bfs() {
    queue<Node> q;
    dista[sx][sy] = 0;
    q.push((Node){sx, sy});

    while (!q.empty()) {
        Node u = q.front();
        q.pop();

        for (int i = 0; i < 8; i++) {
            int nx = u.x + dx[i];
            int ny = u.y + dy[i];

            if (!in_board(nx, ny)) {
                continue;
            }
            if (dista[nx][ny] != -1) {
                continue;
            }

            // 第一次访问到的步数一定最短，直接记录并入队。
            dista[nx][ny] = dista[u.x][u.y] + 1;
            q.push((Node){nx, ny});
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> sx >> sy;

    memset(dista, -1, sizeof(dista)); // -1 同时表示未访问和不可达
    bfs();

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (j > 1) {
                cout << ' ';
            }
            cout << dista[i][j];
        }
        cout << '\n';
    }

    return 0;
}
