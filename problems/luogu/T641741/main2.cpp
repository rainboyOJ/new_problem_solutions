/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-09-05 11:01
 * update_at: 2026-09-05 11:08
 */
// main2.cpp：数字迷宫 BFS，使用 std::queue 实现队列。
#include <bits/stdc++.h>
using namespace std;

int n;                    // 迷宫大小 n * n, 坐标范围 1..n
int sx, sy, tx, ty;       // 起点 (sx,sy) 和终点 (tx,ty) 的坐标
int maze[100][100];       // 迷宫地图, 1 表示墙, 0 表示可以通行
int dis[100][100];        // dis[x][y] 表示起点到 (x,y) 的步数+1, 0 表示还没走到过

// 队列中的元素: 一个格子的坐标
struct node {
    int x, y;
};

int dx[] = {0, 0, 1, -1}; // 上、下、左、右四个方向的行偏移
int dy[] = {1, -1, 0, 0}; // 上、下、左、右四个方向的列偏移

void init() {
    cin >> n;
    cin >> sx >> sy >> tx >> ty;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> maze[i][j];
        }
    }
}

// 从 (x,y) 出发 BFS, 把能到达的每个格子的最短步数写进 dis
void bfs(int x, int y) {
    queue<node> q; // BFS 队列, 存等待扩展的格子
    dis[x][y] = 1; // 起点记为 1 (步数 +1, 0 保留给"未到达"用)
    q.push({x, y});

    while (!q.empty()) {
        node h = q.front();
        q.pop();

        // 枚举上下左右四个方向
        for (int i = 0; i < 4; i++) {
            int nx = h.x + dx[i];
            int ny = h.y + dy[i];

            if (nx < 1 || nx > n || ny < 1 || ny > n) continue; // 出界
            if (maze[nx][ny] == 1) continue;                    // 墙
            if (dis[nx][ny] != 0) continue;                     // 已经访问过

            dis[nx][ny] = dis[h.x][h.y] + 1; // 从当前格多走一步
            q.push({nx, ny});
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    init();
    bfs(sx, sy); // 从起点开始 BFS

    // dis[终点] != 0 说明终点被访问过, 可以到达
    if (dis[tx][ty] != 0) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
    cout << dis[tx][ty]; // 输出步数 +1 (无法到达时是 0)

    return 0;
}
