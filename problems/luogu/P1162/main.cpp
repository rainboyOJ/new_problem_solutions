/**
 * Author by Rainboy blog: https://rainboylv.com github: https://rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */

/* P1162 填涂颜色 */
/* 给矩阵补一圈 0 并从外部 BFS，未被搜索到的 0 就是闭合圈内部。 */

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 35;

int n;
int g[MAXN][MAXN]; // 原矩阵，外围补一圈 0
int vis[MAXN][MAXN]; // 标记外部可达的 0
int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};

void bfs() {
    queue<pair<int, int>> q;
    q.push({0, 0});
    vis[0][0] = 1;

    while (!q.empty()) {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx < 0 || nx > n + 1 || ny < 0 || ny > n + 1) continue;
            if (vis[nx][ny]) continue;
            if (g[nx][ny] == 1) continue; // 墙不能通过
            vis[nx][ny] = 1;
            q.push({nx, ny});
        }
    }
}

int main() {
    cin >> n;
    // 读入矩阵，外围自动补一圈 0
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> g[i][j];
        }
    }

    bfs(); // 从外部 bfs，标记所有外部可达的 0

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (g[i][j] == 1) {
                cout << 1 << " ";
            } else if (vis[i][j]) {
                cout << 0 << " "; // 外部可达，保持 0
            } else {
                cout << 2 << " "; // 内部闭合圈，填 2
            }
        }
        cout << "\n";
    }
    return 0;
}
