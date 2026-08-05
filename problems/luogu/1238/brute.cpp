/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-05 11:20
 * update_at: 2026-08-05 11:20
 */
// brute.cpp：小数据暴力解，用递归回溯枚举所有简单路径，
// 与 main.cpp 独立实现，方向顺序保持一致，用于交叉验证。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 20;

int m, n;
int mp[MAXN][MAXN];
int sx, sy, ex, ey;
bool vis[MAXN][MAXN];
vector<pair<int, int>> path;
bool has_ans;

int dx[4] = {-1, 0, 0, 1};
int dy[4] = {0, -1, 1, 0};

void print_path() {
    for (size_t i = 0; i < path.size(); i++) {
        if (i) cout << "->";
        cout << "(" << path[i].first << "," << path[i].second << ")";
    }
    cout << '\n';
}

void dfs(int x, int y) {
    if (x == ex && y == ey) {
        has_ans = true;
        print_path();
        return;
    }
    for (int k = 0; k < 4; k++) {
        int nx = x + dx[k], ny = y + dy[k];
        if (nx < 1 || nx > m || ny < 1 || ny > n) continue;
        if (mp[nx][ny] == 0 || vis[nx][ny]) continue;
        vis[nx][ny] = true;
        path.push_back({nx, ny});
        dfs(nx, ny);
        path.pop_back();
        vis[nx][ny] = false;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> m >> n;
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++)
            cin >> mp[i][j];
    cin >> sx >> sy >> ex >> ey;

    vis[sx][sy] = true;
    path.push_back({sx, sy});
    dfs(sx, sy);

    if (!has_ans) cout << -1 << '\n';

    return 0;
}
