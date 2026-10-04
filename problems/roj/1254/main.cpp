/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 07:12
 * update_at: 2026-10-05 07:12
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;

typedef long long ll;

int n, m;
char grid[MAXN][MAXN]; // grid[r][c]：迷宫第 r 行第 c 列的字符
bool vis[MAXN][MAXN];  // vis[r][c]：该格是否已经入队，入队即标记防止重复展开
int dist[MAXN][MAXN];  // dist[r][c]：从 S 到该格的最少步数（层号）

int dr[4] = {-1, 1, 0, 0}; // 四个方向的行增量：上、下、左、右
int dc[4] = {0, 0, -1, 1};

// 从 (sr,sc) 到 (tr,tc) 的 BFS 最短路；走不到时返回 -1。
int bfs(int sr, int sc, int tr, int tc) {
    queue<pair<int, int> > q;
    vis[sr][sc] = 1;
    dist[sr][sc] = 0;
    q.push(make_pair(sr, sc));
    while (!q.empty()) {
        int r = q.front().first;
        int c = q.front().second;
        q.pop();
        if (r == tr && c == tc) return dist[r][c]; // 第一次弹出 T 时层号就是答案
        for (int i = 0; i < 4; i++) {
            int nr = r + dr[i];
            int nc = c + dc[i];
            // 合法落点：在网格内、不是墙、没有入队过
            if (nr < 1 || nr > n || nc < 1 || nc > m) continue;
            if (grid[nr][nc] == '#' || vis[nr][nc]) continue;
            vis[nr][nc] = 1;
            dist[nr][nc] = dist[r][c] + 1;
            q.push(make_pair(nr, nc));
        }
    }
    return -1; // S 所在连通分量搜完仍未到 T，无解
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> (grid[i] + 1);
    }

    // 扫描网格定位唯一的起点 S 和出口 T
    int sr = 0, sc = 0, tr = 0, tc = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (grid[i][j] == 'S') { sr = i; sc = j; }
            if (grid[i][j] == 'T') { tr = i; tc = j; }
        }
    }

    int ans = bfs(sr, sc, tr, tc);
    if (ans != -1) cout << ans << endl; // 无解时不输出任何内容

    return 0;
}
