/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 22:48
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;
const int MAX_TIME = 101; // 所有危险在时刻 100 内结束，时刻 101 起所有格子都是安全的

int n, m;
int danger_start[MAXN][MAXN];               // 方格开始危险的时刻，-1 表示从不危险
int danger_end[MAXN][MAXN];                 // 方格危险结束的时刻
int visited[MAXN][MAXN][MAX_TIME + 1];      // visited[r][c][t] 是否恰在时刻 t 到达该格
int distance_to[MAXN][MAXN];                // 时刻 MAX_TIME 之后的普通最短路
int dr[4] = {1, -1, 0, 0};
int dc[4] = {0, 0, 1, -1};

// BFS 状态：行、列、到达时刻
struct State {
    int row, column, time;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> n >> m >> t;
    memset(danger_start, -1, sizeof(danger_start));
    memset(danger_end, -1, sizeof(danger_end));
    for (int i = 1; i <= t; i++) {
        int r, c, a, b;
        cin >> r >> c >> a >> b;
        danger_start[r - 1][c - 1] = a;
        danger_end[r - 1][c - 1] = b;
    }

    // 第一步：带上时间维度的 BFS，把危险时段内的障碍按时刻区分开。
    queue<State> q;
    q.push({0, 0, 0});
    visited[0][0][0] = 1;
    while (!q.empty()) {
        State current = q.front();
        q.pop();
        if (current.row == n - 1 && current.column == m - 1) {
            cout << current.time << '\n';
            return 0;
        }
        if (current.time == MAX_TIME) {
            continue; // 时间维度只记录到 MAX_TIME，之后交给普通 BFS
        }
        int next_time = current.time + 1;
        for (int i = 0; i < 4; i++) {
            int nr = current.row + dr[i];
            int nc = current.column + dc[i];
            if (nr < 0 || nr >= n || nc < 0 || nc >= m) {
                continue;
            }
            if (visited[nr][nc][next_time]) {
                continue;
            }
            // 到达目标格的时刻不能落在它的危险区间内
            if (danger_start[nr][nc] <= next_time && next_time <= danger_end[nr][nc]) {
                continue;
            }
            visited[nr][nc][next_time] = 1;
            q.push({nr, nc, next_time});
        }
    }

    // 第二步：时刻 MAX_TIME 之后网格不再变化，把此时所有可达格作为多源点
    // 做普通 BFS，求出它们到终点的最短剩余步数。
    queue<pair<int, int> > safe_queue;
    memset(distance_to, -1, sizeof(distance_to));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (visited[i][j][MAX_TIME]) {
                safe_queue.push(make_pair(i, j));
                distance_to[i][j] = MAX_TIME;
            }
        }
    }
    while (!safe_queue.empty()) {
        pair<int, int> current = safe_queue.front();
        safe_queue.pop();
        for (int i = 0; i < 4; i++) {
            int nr = current.first + dr[i];
            int nc = current.second + dc[i];
            if (nr < 0 || nr >= n || nc < 0 || nc >= m) {
                continue;
            }
            if (distance_to[nr][nc] != -1) {
                continue;
            }
            distance_to[nr][nc] = distance_to[current.first][current.second] + 1;
            safe_queue.push(make_pair(nr, nc));
        }
    }

    cout << distance_to[n - 1][m - 1] << '\n';
    return 0;
}