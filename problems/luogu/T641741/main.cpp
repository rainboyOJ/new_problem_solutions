/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-05 11:20
 * update_at: 2026-09-05 11:08
 */
// 用固定数组和 std::queue 做多组网格 BFS，求 S 到 E 的最短步数。
#include <iostream>
#include <queue>
using namespace std;

const int MAXN = 205;

struct Point {
    int x, y;
};

int R, C;                   // 当前这组数据的地图大小 R 行 C 列
char grid[MAXN][MAXN];      // 迷宫地图
int dist[MAXN][MAXN];       // dist[i][j] 表示从 S 走到 (i,j) 的最短步数, -1 表示还没走到
int sx, sy, ex, ey;         // 起点 S 与终点 E 的坐标

int dx[4] = {-1, 1, 0, 0}; // 上、下、左、右四个方向的行偏移
int dy[4] = {0, 0, -1, 1}; // 上、下、左、右四个方向的列偏移

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T; // 一共有 T 组数据
    cin >> T;

    while (T--) {
        cin >> R >> C;

        for (int i = 0; i < R; i++) {
            for (int j = 0; j < C; j++) {
                cin >> grid[i][j];
                dist[i][j] = -1; // 每组数据开始时全部标记为未到达

                if (grid[i][j] == 'S') { // 记录起点
                    sx = i;
                    sy = j;
                }
                if (grid[i][j] == 'E') { // 记录终点
                    ex = i;
                    ey = j;
                }
            }
        }

        std::queue<Point> q; // BFS 队列, 存等待扩展的格子
        dist[sx][sy] = 0;    // 起点步数为 0
        q.push({sx, sy});

        while (!q.empty()) {
            Point now = q.front();
            q.pop();

            // BFS 按层扩展, 第一次遇到终点时步数已经最小, 可以提前结束
            if (now.x == ex && now.y == ey) break;

            for (int k = 0; k < 4; k++) {
                int nx = now.x + dx[k];
                int ny = now.y + dy[k];

                if (nx < 0 || nx >= R || ny < 0 || ny >= C) continue; // 越界
                if (grid[nx][ny] == '#') continue;                    // 墙壁不可走
                if (dist[nx][ny] != -1) continue;                     // 已经到达过, 不再入队

                dist[nx][ny] = dist[now.x][now.y] + 1; // 从当前格多走一步
                q.push({nx, ny});
            }
        }

        if (dist[ex][ey] == -1) cout << "oop!\n"; // 终点始终没被访问, 不可达
        else cout << dist[ex][ey] << '\n';        // 输出最短步数
    }

    return 0;
}
