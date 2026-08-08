/**
 * Author by Rainboy blog: https://rainboylv.com github: https://rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */

/* P1596 [USACO10OCT] Lake Counting S */
/* 扫描网格，每遇到未访问水格就用八方向 DFS 淹掉整个连通块。 */

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;

int n, m;
char g[MAXN][MAXN]; // 网格
int dx[8] = { -1, -1, -1, 0, 0, 1, 1, 1 };
int dy[8] = { -1, 0, 1, -1, 1, -1, 0, 1 };

// DFS 标记一个连通块
void dfs(int x, int y) {
    g[x][y] = '.'; // 标记已访问
    for (int i = 0; i < 8; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx >= 1 && nx <= n && ny >= 1 && ny <= m && g[nx][ny] == 'W') {
            dfs(nx, ny);
        }
    }
}

int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> (g[i] + 1);
    }

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (g[i][j] == 'W') {
                ans++;
                dfs(i, j); // 标记整个水塘
            }
        }
    }

    cout << ans << "\n";
    return 0;
}
