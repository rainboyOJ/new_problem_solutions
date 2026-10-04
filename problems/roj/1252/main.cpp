/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 07:02
 * update_at: 2026-10-05 07:02
 */
// main.cpp：网格 BFS 求从左上角到右下角的最少经过格子数（含起点终点）。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 45;

int R, C;
char grid[MAXN][MAXN];           // 网格，'.' 可通行，'#' 障碍
bool vis[MAXN][MAXN];            // 入队即标记，避免重复展开

int dr[4] = {-1, 1, 0, 0};       // 上、下、左、右四个移动方向
int dc[4] = {0, 0, -1, 1};

// 从左上角 (0,0) 到右下角 (R-1,C-1) 的最少经过格子数；数据保证有解。
int bfs_min_cells() {
    queue<pair<int,int>> q;
    vis[0][0] = true;
    q.push({0, 0});
    int cells = 1;               // 起点本身算 1 格
    while (!q.empty()) {
        int sz = (int)q.size();  // 当前层格子数：BFS 按层扩展，便于统计步数
        for (int i = 0; i < sz; i++) {
            auto cur = q.front(); q.pop();
            int r = cur.first;
            int c = cur.second;
            if (r == R - 1 && c == C - 1) return cells; // 首次到达终点即最短
            for (int k = 0; k < 4; k++) {
                int nr = r + dr[k];
                int nc = c + dc[k];
                if (nr < 0 || nr >= R || nc < 0 || nc >= C) continue;
                if (grid[nr][nc] != '.') continue;
                if (vis[nr][nc]) continue;
                vis[nr][nc] = true;
                q.push({nr, nc});
            }
        }
        cells++;                 // 处理完一层，格子数 +1
    }
    return -1;                   // 防御：题面保证有解，正常不会走到这里
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> R >> C;
    for (int i = 0; i < R; i++) {
        cin >> grid[i];
    }

    int ans = bfs_min_cells();
    cout << ans << "\n";

    return 0;
}