/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-17 13:04
 * update_at: 2026-08-17 13:10
 */
#include <bits/stdc++.h>
using namespace std;

const int maxn = 105;

int R, C;
int h[maxn][maxn];     // h[i][j] 格子 (i,j) 的高度
int f[maxn][maxn];     // f[i][j] 从 (i,j) 出发的最长滑坡长度，-1 表示还没计算

int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};

// 计算从 (x,y) 出发能滑出的最长长度（记忆化搜索）
int dfs(int x, int y) {
    if (f[x][y] != -1) return f[x][y];
    int res = 1;
    for (int k = 0; k < 4; k++) {
        int nx = x + dx[k], ny = y + dy[k];
        if (nx < 1 || nx > R || ny < 1 || ny > C) continue;
        if (h[nx][ny] >= h[x][y]) continue;   // 只能滑到高度严格更小的格子
        res = max(res, dfs(nx, ny) + 1);
    }
    return f[x][y] = res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> R >> C;
    for (int i = 1; i <= R; i++)
        for (int j = 1; j <= C; j++)
            cin >> h[i][j];

    memset(f, -1, sizeof(f));

    int ans = 0;
    for (int i = 1; i <= R; i++)
        for (int j = 1; j <= C; j++)
            ans = max(ans, dfs(i, j));

    cout << ans << endl;
    return 0;
}
