/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-05 11:20
 * update_at: 2026-08-29 17:24
 */
// 用固定数组和 std::queue 做多组网格 BFS，求 S 到 E 的最短步数。
#include <iostream>
#include <queue>
using namespace std;

const int MAXN = 205;

struct Point {
    int x, y;
};

int R, C;
char grid[MAXN][MAXN];
int dist[MAXN][MAXN];
int sx, sy, ex, ey;

int dx[4] = {-1, 1, 0, 0}; // 上、下、左、右
int dy[4] = {0, 0, -1, 1};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        cin >> R >> C;

        for (int i = 0; i < R; i++) {
            for (int j = 0; j < C; j++) {
                cin >> grid[i][j];
                dist[i][j] = -1;
                if (grid[i][j] == 'S') {
                    sx = i;
                    sy = j;
                }
                if (grid[i][j] == 'E') {
                    ex = i;
                    ey = j;
                }
            }
        }

        std::queue<Point> q;
        dist[sx][sy] = 0;
        q.push({sx, sy});

        while (!q.empty()) {
            Point now = q.front();
            q.pop();

            if (now.x == ex && now.y == ey) break;

            for (int k = 0; k < 4; k++) {
                int nx = now.x + dx[k];
                int ny = now.y + dy[k];

                if (nx < 0 || nx >= R || ny < 0 || ny >= C) continue;
                if (grid[nx][ny] == '#') continue;
                if (dist[nx][ny] != -1) continue;

                dist[nx][ny] = dist[now.x][now.y] + 1;
                q.push({nx, ny});
            }
        }

        if (dist[ex][ey] == -1) cout << "oop!\n";
        else cout << dist[ex][ey] << '\n';
    }

    return 0;
}
