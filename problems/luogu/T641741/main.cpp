/**
 * T641741 献给阿尔吉侬的花束
 * 多测试用例网格 BFS 最短路
 * 约束: T≤10, R,C≤200, 单 BFS O(RC)
 */
#include <bits/stdc++.h>
using namespace std;

const int dx[4] = {-1, 1, 0, 0};
const int dy[4] = {0, 0, -1, 1};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    if (!(cin >> T)) return 0;
    while (T--) {
        int R, C;
        cin >> R >> C;
        vector<string> g(R);
        for (int i = 0; i < R; ++i) cin >> g[i];

        int sx = -1, sy = -1, ex = -1, ey = -1;
        for (int i = 0; i < R; ++i) {
            for (int j = 0; j < C; ++j) {
                if (g[i][j] == 'S') { sx = i; sy = j; }
                else if (g[i][j] == 'E') { ex = i; ey = j; }
            }
        }

        vector<vector<int>> dist(R, vector<int>(C, -1));
        queue<pair<int,int>> q;
        dist[sx][sy] = 0;
        q.emplace(sx, sy);

        while (!q.empty()) {
            auto [x, y] = q.front(); q.pop();
            if (x == ex && y == ey) break;
            for (int d = 0; d < 4; ++d) {
                int nx = x + dx[d], ny = y + dy[d];
                if (nx < 0 || nx >= R || ny < 0 || ny >= C) continue;
                if (g[nx][ny] == '#') continue;
                if (dist[nx][ny] != -1) continue;
                dist[nx][ny] = dist[x][y] + 1;
                q.emplace(nx, ny);
            }
        }

        if (dist[ex][ey] == -1) cout << "oop!\n";
        else cout << dist[ex][ey] << '\n';
    }
    return 0;
}