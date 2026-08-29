/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-29 17:32
 * update_at: 2026-08-29 17:32
 */
// main-dfs.cpp：补一圈 0，从外围用 DFS 标记所有与外界连通的 0。
#include <iostream>
using namespace std;

const int MAXN = 35;

int n;
int g[MAXN][MAXN];       // 0 可以走，1 是墙
bool vis[MAXN][MAXN];    // 从外部可以到达的 0

int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};

// 从外围 (0,0) 出发，标记所有与外界连通的 0。
void dfs(int x, int y) {
    vis[x][y] = true;

    for (int k = 0; k < 4; k++) {
        int nx = x + dx[k];
        int ny = y + dy[k];

        if (nx < 0 || nx > n + 1 || ny < 0 || ny > n + 1)
            continue;
        if (vis[nx][ny])
            continue;
        if (g[nx][ny] == 1)
            continue;

        dfs(nx, ny);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    // 全局数组默认为 0，天然补出一圈外围边框。
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> g[i][j];
        }
    }

    dfs(0, 0);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (j > 1)
                cout << " ";

            if (g[i][j] == 1)
                cout << 1;
            else if (vis[i][j])
                cout << 0;
            else
                cout << 2;
        }
        cout << "\n";
    }

    return 0;
}
