/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 07:11
 * update_at: 2026-10-05 07:11
 */
#include <iostream>
#include <queue>
using namespace std;

typedef long long ll;

const int N = 5;           // 迷宫固定 5×5
const int DIR = 4;         // 四个方向
int maze[N][N];            // 0 通路，1 墙壁
int pr[N][N], pc[N][N];    // 每个格子前驱坐标，同时充当访问标记：pr=-1 表示未访问
int dr[DIR] = {-1, 1, 0, 0};
int dc[DIR] = {0, 0, -1, 1};

// BFS 求最短路，同时记录前驱；首次到达某格即最短步数
void bfs_path() {
    queue<pair<int, int> > q;
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            pr[i][j] = -1;
    pr[0][0] = -2;         // 起点特殊标记，无前驱
    pc[0][0] = -2;
    q.push(make_pair(0, 0));

    while (!q.empty()) {
        int r = q.front().first;
        int c = q.front().second;
        q.pop();
        for (int k = 0; k < DIR; ++k) {
            int nr = r + dr[k];
            int nc = c + dc[k];
            if (nr < 0 || nr >= N || nc < 0 || nc >= N) continue;
            if (maze[nr][nc] == 1) continue;        // 墙
            if (pr[nr][nc] != -1) continue;         // 已访问
            pr[nr][nc] = r;                          // 登记前驱
            pc[nr][nc] = c;
            q.push(make_pair(nr, nc));
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            cin >> maze[i][j];

    bfs_path();

    // 从终点沿前驱回溯到起点
    int r = N - 1, c = N - 1;
    pair<int, int> path[N * N];
    int len = 0;
    while (!(r == 0 && c == 0)) {
        path[len++] = make_pair(r, c);
        int nr = pr[r][c];
        int nc = pc[r][c];
        r = nr;
        c = nc;
    }
    path[len++] = make_pair(0, 0);

    // 反转输出
    for (int i = len - 1; i >= 0; --i)
        cout << '(' << path[i].first << ", " << path[i].second << ')' << '\n';

    return 0;
}
