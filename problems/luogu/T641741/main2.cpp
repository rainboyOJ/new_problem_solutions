/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-09-05 11:01
 * update_at: 2026-09-05 11:01
 */
// main2.cpp：数字迷宫 BFS，使用 std::queue 实现队列。
#include <bits/stdc++.h>
using namespace std;

int n;
int sx, sy, tx, ty;    // 起点和终点坐标
int maze[100][100];    // 迷宫地图, 1 表示墙, 0 表示可以通行
int dis[100][100];     // dis[x][y] 表示起点到 (x,y) 的步数+1, 0 表示还没走到过

struct node {
    int x, y;
};

int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

void init() {
    cin >> n;
    cin >> sx >> sy >> tx >> ty;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> maze[i][j];
        }
    }
}

void bfs(int x, int y) {
    queue<node> q;
    q.push({x, y});
    dis[x][y] = 1;

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

            dis[nx][ny] = dis[h.x][h.y] + 1;
            q.push({nx, ny});
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    init();
    bfs(sx, sy);

    if (dis[tx][ty] != 0) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
    cout << dis[tx][ty];

    return 0;
}
