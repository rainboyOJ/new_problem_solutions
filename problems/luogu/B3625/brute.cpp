/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-05 11:15
 * update_at: 2026-08-05 11:15
 */
// brute.cpp：小数据暴力解，用 DFS 回溯找一条从 (1,1) 到 (n,m) 的路径。
// 与 BFS 独立实现，用来对拍验证可达性判断。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;

int n, m;
char mp[MAXN][MAXN];
bool vis[MAXN][MAXN];

int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};

// 从 (x, y) 出发是否有一条路能到 (n, m)
bool dfs(int x, int y) {
    if (x == n && y == m) return true;
    for (int k = 0; k < 4; k++) {
        int nx = x + dx[k], ny = y + dy[k];
        if (nx < 1 || nx > n || ny < 1 || ny > m) continue;
        if (mp[nx][ny] == '#' || vis[nx][ny]) continue;
        vis[nx][ny] = true;
        if (dfs(nx, ny)) return true;
        vis[nx][ny] = false;   // 回溯：撤销访问
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> (mp[i] + 1);

    vis[1][1] = true;
    cout << (dfs(1, 1) ? "Yes\n" : "No\n");

    return 0;
}
