/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-05 11:20
 * update_at: 2026-08-05 11:20
 */
// DFS 枚举所有简单路径：路径上不能重复经过点，方向按 上、左、右、下 顺序尝试。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 20;

int m, n;               // m 行 n 列
int mp[MAXN][MAXN];     // 1 可走，0 不可走
int sx, sy, ex, ey;     // 起点、终点
bool vis[MAXN][MAXN];   // 当前路径上是否已走过
int path_x[MAXN * MAXN], path_y[MAXN * MAXN];   // 路径上的点
int path_len;           // 当前路径长度
bool has_ans;           // 是否至少找到一条路径

int dx[4] = {-1, 0, 0, 1};   // 上 左 右 下
int dy[4] = {0, -1, 1, 0};

void print_path() {
    for (int i = 0; i < path_len; i++) {
        if (i) cout << "->";
        cout << "(" << path_x[i] << "," << path_y[i] << ")";
    }
    cout << '\n';
}

// 当前在 (x, y)，尝试走到终点
void dfs(int x, int y) {
    if (x == ex && y == ey) {   // 到达终点，输出当前完整路径
        has_ans = true;
        print_path();
        return;
    }

    for (int k = 0; k < 4; k++) {   // 按 上左下右 顺序尝试
        int nx = x + dx[k], ny = y + dy[k];
        if (nx < 1 || nx > m || ny < 1 || ny > n) continue;   // 出界
        if (mp[nx][ny] == 0) continue;                        // 不可走
        if (vis[nx][ny]) continue;                            // 路径不能重复

        vis[nx][ny] = true;
        path_x[path_len] = nx;
        path_y[path_len] = ny;
        path_len++;

        dfs(nx, ny);

        path_len--;              // 回溯：撤销这一步
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
    path_x[0] = sx;
    path_y[0] = sy;
    path_len = 1;

    dfs(sx, sy);

    if (!has_ans) cout << -1 << '\n';

    return 0;
}
