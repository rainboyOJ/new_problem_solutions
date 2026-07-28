/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-28 17:09
 * update_at: 2026-07-28 17:09
 */
// main2.cpp：两次 BFS。第一次探索连通分量（只判断不修改），第二次 flood fill 标记已访问。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;

int n, m;
char g[MAXN][MAXN];   // 网格
bool vis[MAXN][MAXN]; // BFS1 专用访问标记
int dx[8] = { -1, -1, -1, 0, 0, 1, 1, 1 };
int dy[8] = { -1, 0, 1, -1, 1, -1, 0, 1 };

// BFS1：从 (sx,sy) 出发探索，不修改网格。
// 如果发现至少一个 W 格子（含自身），说明能走出去，返回 true。
bool bfs1(int sx, int sy) {
    if (g[sx][sy] != 'W' || vis[sx][sy])
        return false;

    queue<pair<int,int>> q;
    q.push({sx, sy});
    vis[sx][sy] = true;

    while (!q.empty()) {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();
        for (int i = 0; i < 8; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx < 1 || nx > n || ny < 1 || ny > m)
                continue;
            if (vis[nx][ny] || g[nx][ny] != 'W')
                continue;
            vis[nx][ny] = true;
            q.push({nx, ny});
        }
    }
    return true;
}

// BFS2：从 (sx,sy) 出发 flood fill，把整个水塘改为 '2'
void bfs2(int sx, int sy) {
    queue<pair<int,int>> q;
    q.push({sx, sy});
    g[sx][sy] = '2';

    while (!q.empty()) {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();
        for (int i = 0; i < 8; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx < 1 || nx > n || ny < 1 || ny > m)
                continue;
            if (g[nx][ny] != 'W')
                continue;
            g[nx][ny] = '2';
            q.push({nx, ny});
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
            if (g[i][j] == 'W' && !vis[i][j]) {
                // BFS1：判断从该点能不能走出去（发现新水塘）
                if (bfs1(i, j)) {
                    ans++;
                    // BFS2：如果不能走出去（实际是新水塘），第二次 BFS 标记
                    bfs2(i, j);
                }
            }
        }
    }

    cout << ans << '\n';
    return 0;
}
