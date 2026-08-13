/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-13 13:27
 * update_at: 2026-08-13 13:33
 */
// brute.cpp：本地对拍验证代码，不是独立的教学暴力层。
// 洪水填充（Flood Fill）本身就是本题的直接做法，没有"朴素 -> 优化"的演进，
// 单独的暴力只会和 main.cpp 重复；这里用与 main.cpp 不同的结构
// （递归 DFS + visited 数组，main.cpp 是 BFS + 原地修改网格）再实现一遍，
// 结构互相独立，用于随机对拍相互印证。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;

int n, m;
char g[MAXN][MAXN];          // 网格：'W' 是水，'.' 是干地
bool vis[MAXN][MAXN];        // vis[x][y] 标记格子是否已属于某个统计过的水塘
int dx[8] = { -1, -1, -1, 0, 0, 1, 1, 1 }; // 八方向
int dy[8] = { -1, 0, 1, -1, 1, -1, 0, 1 };

// 递归 DFS 标记一个水塘：从 (x, y) 出发，把所有八方向可达的未访问水格标掉。
void dfs(int x, int y) {
    vis[x][y] = true;
    for (int i = 0; i < 8; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx >= 1 && nx <= n && ny >= 1 && ny <= m && !vis[nx][ny] && g[nx][ny] == 'W') {
            dfs(nx, ny);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> (g[i] + 1);
    }

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (g[i][j] == 'W' && !vis[i][j]) { // 未访问的水格 = 新水塘
                ans++;
                dfs(i, j);
            }
        }
    }

    cout << ans << "\n";
    return 0;
}
