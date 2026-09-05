/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-09-05 11:01
 * update_at: 2026-09-05 11:12
 */
// main2.cpp：字符迷宫 BFS（多组数据），使用 std::queue 实现队列。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 205;

int R, C;                 // 当前这组数据的迷宫大小: R 行 C 列
char maze[MAXN][MAXN];    // 迷宫地图, '#' 表示墙, '.' 表示空地
int dis[MAXN][MAXN];      // dis[x][y] 表示从 S 到 (x,y) 的最短步数, -1 表示没走到过
int sx, sy, tx, ty;       // 起点 S 和终点 E 的坐标

// 队列中的元素: 一个格子的坐标
struct node {
    int x, y;
};

int dx[] = {-1, 1, 0, 0}; // 上、下、左、右四个方向的行偏移
int dy[] = {0, 0, -1, 1}; // 上、下、左、右四个方向的列偏移

// 读入一组数据, 同时记录起点和终点的坐标
void init() {
    cin >> R >> C;
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            cin >> maze[i][j];
            dis[i][j] = -1; // 每组开始时全部标记为未到达

            if (maze[i][j] == 'S') { // 记录起点
                sx = i;
                sy = j;
            }
            if (maze[i][j] == 'E') { // 记录终点
                tx = i;
                ty = j;
            }
        }
    }
}

// 从 (x,y) 出发 BFS, 把能到达的每个格子的最短步数写进 dis
void bfs(int x, int y) {
    queue<node> q; // BFS 队列, 存等待扩展的格子
    dis[x][y] = 0; // 起点步数为 0
    q.push({x, y});

    while (!q.empty()) {
        node h = q.front();
        q.pop();

        // 枚举上下左右四个方向
        for (int i = 0; i < 4; i++) {
            int nx = h.x + dx[i];
            int ny = h.y + dy[i];

            if (nx < 0 || nx >= R || ny < 0 || ny >= C) continue; // 出界
            if (maze[nx][ny] == '#') continue;                    // 墙
            if (dis[nx][ny] != -1) continue;                      // 已经访问过

            dis[nx][ny] = dis[h.x][h.y] + 1; // 从当前格多走一步
            q.push({nx, ny});
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T; // 一共有 T 组数据
    cin >> T;

    while (T--) {
        init();
        bfs(sx, sy); // 从起点开始 BFS

        // dis[终点] != -1 说明终点可达, 输出最短步数
        if (dis[tx][ty] != -1) {
            cout << dis[tx][ty] << '\n';
        } else {
            cout << "oop!\n";
        }
    }

    return 0;
}
