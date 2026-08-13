/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-13 13:30
 * update_at: 2026-08-13 13:31
 */
/* P1162 填涂颜色 */
/* 给矩阵补一圈 0 并从外部 BFS，未被外部搜索到的 0 就是闭合圈内部。 */

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 35;

int n;
int g[MAXN][MAXN];    // 原矩阵，下标 0..n+1，外围自动补一圈 0
int vis[MAXN][MAXN];  // vis[x][y] = 1 表示 (x,y) 是从外部可达的 0
int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};

// 从矩阵外的一点 (0,0) 出发 BFS，把所有能走到且值为 0 的格子标记为外部可达。
void bfs() {
    queue<pair<int, int>> q;
    q.push({0, 0});
    vis[0][0] = 1;

    while (!q.empty()) {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();

        // 四方向扩展，只走值为 0 且未访问过的格子。
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx < 0 || nx > n + 1 || ny < 0 || ny > n + 1) continue;
            if (vis[nx][ny]) continue;
            if (g[nx][ny] == 1) continue; // 墙 1 不能通过
            vis[nx][ny] = 1;
            q.push({nx, ny});
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    // 读入 n*n 矩阵；全局数组初始为 0，相当于自动补了一圈 0。
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> g[i][j];
        }
    }

    bfs(); // 从外部 BFS，标记所有与外界连通的 0

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (g[i][j] == 1) {
                cout << 1;       // 墙保持不变
            } else if (vis[i][j]) {
                cout << 0;       // 外部可达的 0，保持原样
            } else {
                cout << 2;       // 未被访问的 0 在闭合圈内，填 2
            }
            if (j < n) cout << " ";
        }
        cout << "\n";
    }
    return 0;
}
