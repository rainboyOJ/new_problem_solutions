/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-05 11:10
 * update_at: 2026-08-05 11:10
 */
// brute.cpp：小数据暴力解，对每个询问直接一步步模拟移动，
// 用 vis 时间戳判断是否进入环（重复访问同一格子）。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;

int n, m, q;
int a[MAXN][MAXN];
int vis[MAXN][MAXN];   // 本次模拟中是否访问过

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
        memset(vis, 0, sizeof(vis));

        int step = 0;
        while (true) {
            if (x < 1 || x > n || y < 1 || y > m) {   // 离开迷宫
                cout << step << '\n';
                break;
            }
            if (vis[x][y]) {   // 重复访问：进入环，永远出不去
                cout << -1 << '\n';
                break;
            }
            vis[x][y] = 1;
            if (a[x][y] == 1) x--;
            else if (a[x][y] == 2) x++;
            else if (a[x][y] == 3) y--;
            else y++;
            step++;
        }
    }

    return 0;
}
