/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-29 17:35
 * update_at: 2026-08-29 17:35
 */
// main2-dfs.cpp：第一次 DFS 判断区域是否接触边界，第二次 DFS 填涂内部区域。
#include <iostream>
using namespace std;

const int MAXN = 35;

int n;
int g[MAXN][MAXN];       // 0: 空地，1: 墙，2: 已填涂
bool vis[MAXN][MAXN];    // 第一次 DFS 的访问标记

int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};

bool can_get_out;

// 搜索一个 0 连通区域，并判断它是否能到达矩阵边界。
void dfs1(int x, int y) {
    vis[x][y] = true;

    if (x == 1 || x == n || y == 1 || y == n)
        can_get_out = true;

    for (int k = 0; k < 4; k++) {
        int nx = x + dx[k];
        int ny = y + dy[k];

        if (nx < 1 || nx > n || ny < 1 || ny > n)
            continue;
        if (vis[nx][ny])
            continue;
        if (g[nx][ny] != 0)
            continue;

        dfs1(nx, ny);
    }
}

// 把一个已经确认封闭的 0 连通区域全部填成 2。
void dfs2(int x, int y) {
    g[x][y] = 2;

    for (int k = 0; k < 4; k++) {
        int nx = x + dx[k];
        int ny = y + dy[k];

        if (nx < 1 || nx > n || ny < 1 || ny > n)
            continue;
        if (g[nx][ny] != 0)
            continue;

        dfs2(nx, ny);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> g[i][j];
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (g[i][j] != 0 || vis[i][j])
                continue;

            can_get_out = false;
            dfs1(i, j);
            if (!can_get_out)
                dfs2(i, j);
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (j > 1)
                cout << " ";
            cout << g[i][j];
        }
        cout << "\n";
    }

    return 0;
}
