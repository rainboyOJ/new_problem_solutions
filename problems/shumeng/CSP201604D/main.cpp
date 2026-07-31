/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-07-31 20:14
 */
#include <bits/stdc++.h>
using namespace std;

struct State { int row, column, time; };

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, t;
    cin >> n >> m >> t;
    int begin_danger[105][105], end_danger[105][105];
    memset(begin_danger, -1, sizeof(begin_danger));
    memset(end_danger, -1, sizeof(end_danger));
    while (t--) {
        int r, c, a, b;
        cin >> r >> c >> a >> b;
        begin_danger[r - 1][c - 1] = a;
        end_danger[r - 1][c - 1] = b;
    }
    int visited[105][105][102] = {};
    queue<State> q;
    q.push({0, 0, 0}); visited[0][0][0] = 1;
    int dr[4] = {1, -1, 0, 0}, dc[4] = {0, 0, 1, -1};
    while (!q.empty()) {
        State current = q.front(); q.pop();
        if (current.row == n - 1 && current.column == m - 1) {
            cout << current.time << '\n'; return 0;
        }
        if (current.time == 101) continue;
        int next_time = current.time + 1;
        for (int i = 0; i < 4; i++) {
            int nr = current.row + dr[i], nc = current.column + dc[i];
            if (nr < 0 || nr >= n || nc < 0 || nc >= m || visited[nr][nc][next_time]) continue;
            if (begin_danger[nr][nc] <= next_time && next_time <= end_danger[nr][nc]) continue;
            visited[nr][nc][next_time] = 1;
            q.push({nr, nc, next_time});
        }
    }
    queue<pair<int, int> > safe_queue;
    int distance[105][105];
    memset(distance, -1, sizeof(distance));
    for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
        if (visited[i][j][101]) safe_queue.push(make_pair(i, j)), distance[i][j] = 101;
    }
    while (!safe_queue.empty()) {
        pair<int, int> current = safe_queue.front(); safe_queue.pop();
        for (int i = 0; i < 4; i++) {
            int nr = current.first + dr[i], nc = current.second + dc[i];
            if (nr < 0 || nr >= n || nc < 0 || nc >= m || distance[nr][nc] != -1) continue;
            distance[nr][nc] = distance[current.first][current.second] + 1;
            safe_queue.push(make_pair(nr, nc));
        }
    }
    cout << distance[n - 1][m - 1] << '\n';
    return 0;
}
