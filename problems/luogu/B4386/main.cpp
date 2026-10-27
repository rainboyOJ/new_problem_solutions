/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-05 11:10
 * update_at: 2026-08-05 11:10
 */
// 记忆化搜索：从每个格子出发只有一条固定路线（出度为 1 的函数图），
// 用三色标记 DFS 记录每个格子的答案，遇到栈中节点即进入环。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;

int n, m, q;
int a[MAXN][MAXN];        // 1 上 2 下 3 左 4 右
int f[MAXN][MAXN];        // 0 未访问，-2 在递归栈中，-1 走不出，>0 步数

// 返回从 (x, y) 出发离开迷宫需要的步数；永远走不出返回 -1
int dfs(int x, int y) {
    if (x < 1 || x > n || y < 1 || y > m) return 0;   // 已经离开迷宫
    if (f[x][y] == -2) return -1;                      // 回到栈中节点：成环
    if (f[x][y] != 0) return f[x][y];                  // 已算出答案（含 -1）

    f[x][y] = -2;   // 标记当前节点在递归栈中

    int nx = x, ny = y;
    if (a[x][y] == 1) nx--;
    else if (a[x][y] == 2) nx++;
    else if (a[x][y] == 3) ny--;
    else ny++;

    int res = dfs(nx, ny);
    f[x][y] = (res == -1) ? -1 : res + 1;
    return f[x][y];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> q;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cin >> a[i][j];

    for (int t = 0; t < q; t++) {
        int x, y;
        cin >> x >> y;
        cout << dfs(x, y) << '\n';
    }

    return 0;
}
