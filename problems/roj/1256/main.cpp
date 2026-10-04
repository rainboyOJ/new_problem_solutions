/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 07:12
 * update_at: 2026-10-05 07:12
 */

#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
#include <utility>
using namespace std;

typedef long long ll;

const int MAXN = 205;

int R, C;
char g[MAXN][MAXN]; // 地图，'S' 起点、'E' 终点、'.' 可通行、'#' 障碍
int dist_[MAXN][MAXN]; // 到达 (r,c) 的最短步数，-1 表示未访问

int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};

// BFS 找 S 到 E 的最少步数；不可达返回 -1
int bfs(int sr, int sc, int tr, int tc) {
    for (int r = 0; r < R; ++r)
        for (int c = 0; c < C; ++c)
            dist_[r][c] = -1;

    queue<pair<int,int> > q;
    dist_[sr][sc] = 0;
    q.push(make_pair(sr, sc));

    while (!q.empty()) {
        pair<int,int> cur = q.front();
        q.pop();
        int r = cur.first;
        int c = cur.second;
        if (r == tr && c == tc) return dist_[r][c];
        for (int k = 0; k < 4; ++k) {
            int nr = r + dr[k];
            int nc = c + dc[k];
            if (nr < 0 || nr >= R || nc < 0 || nc >= C) continue;
            if (g[nr][nc] == '#') continue;
            if (dist_[nr][nc] != -1) continue;
            dist_[nr][nc] = dist_[r][c] + 1;
            q.push(make_pair(nr, nc));
        }
    }
    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    if (!(cin >> T)) return 0;
    for (int t = 0; t < T; ++t) {
        cin >> R >> C;
        for (int r = 0; r < R; ++r) {
            for (int c = 0; c < C; ++c) {
                cin >> g[r][c];
            }
        }

        int sr = 0, sc = 0, tr = 0, tc = 0;
        for (int r = 0; r < R; ++r) {
            for (int c = 0; c < C; ++c) {
                if (g[r][c] == 'S') { sr = r; sc = c; }
                else if (g[r][c] == 'E') { tr = r; tc = c; }
            }
        }

        int ans = bfs(sr, sc, tr, tc);
        if (ans == -1) cout << "oop!";
        else cout << ans;
        if (t != T - 1) cout << "\n";
    }
    return 0;
}