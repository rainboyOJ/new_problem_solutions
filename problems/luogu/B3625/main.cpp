/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-05 11:15
 * update_at: 2026-08-05 11:15
 */
// BFS 判断 (1,1) 能否到达 (n,m)：逐层扩展，每个点只访问一次。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;

int n, m;
char mp[MAXN][MAXN];       // # 墙，. 空地
bool vis[MAXN][MAXN];      // 是否已入队

int dx[4] = {-1, 0, 1, 0}; // 上右下左
int dy[4] = {0, 1, 0, -1};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;

    // 双重循环逐字符读入迷宫
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cin >> mp[i][j];

    queue<pair<int, int>> q;
    q.push({1, 1});
    vis[1][1] = true;

    while (!q.empty()) {
        int x = q.front().first, y = q.front().second;
        q.pop();

        if (x == n && y == m) {   // 到达终点
            cout << "Yes\n";
            return 0;
        }

        for (int k = 0; k < 4; k++) {
            int nx = x + dx[k], ny = y + dy[k];
            if (nx < 1 || nx > n || ny < 1 || ny > m) continue;   // 出界
            if (mp[nx][ny] == '#') continue;                      // 墙
            if (vis[nx][ny]) continue;                            // 已访问
            vis[nx][ny] = true;
            q.push({nx, ny});
        }
    }

    cout << "No\n";
    return 0;
}
