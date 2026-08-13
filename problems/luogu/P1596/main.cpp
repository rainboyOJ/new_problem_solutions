/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-08-13 13:33
 */
/* P1596 [USACO10OCT] Lake Counting S */
/* 扫描网格，每遇到未访问水格就用八方向 BFS 淹掉整个连通块并把答案加一。 */

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;

int n, m;
char g[MAXN][MAXN]; // 网格：'W' 是水，'.' 是干地
int dx[8] = { -1, -1, -1, 0, 0, 1, 1, 1 }; // 八方向：上下左右加四条对角线
int dy[8] = { -1, 0, 1, -1, 1, -1, 0, 1 };

// BFS 从 (sx, sy) 出发，把整个水塘里的 'W' 全部标记成 '.'。
void flood_fill(int sx, int sy) {
    queue<pair<int, int>> q;
    g[sx][sy] = '.';
    q.push(make_pair(sx, sy));

    while (!q.empty()) {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();
        // 向八个方向扩展，未访问的水格直接标记后入队。
        for (int i = 0; i < 8; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx >= 1 && nx <= n && ny >= 1 && ny <= m && g[nx][ny] == 'W') {
                g[nx][ny] = '.'; // 入队前标记，避免同一个格子重复入队
                q.push(make_pair(nx, ny));
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> (g[i] + 1);
    }

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (g[i][j] == 'W') { // 遇到未访问的水格，必然是一个新水塘
                ans++;
                flood_fill(i, j);
            }
        }
    }

    cout << ans << "\n";
    return 0;
}
