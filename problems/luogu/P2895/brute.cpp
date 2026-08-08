#include <bits/stdc++.h>
using namespace std;

const int LIM = 25;
const int INF = 0x3f3f3f3f;

int m;
int danger_time[LIM][LIM];
bool vis[LIM][LIM][80];
int dx[5] = {0, 1, -1, 0, 0};
int dy[5] = {0, 0, 0, 1, -1};

struct Node {
    int x;
    int y;
    int t;
};

bool in_board(int x, int y) {
    return x >= 0 && x < LIM && y >= 0 && y < LIM;
}

int solve() {
    if (danger_time[0][0] == 0) {
        return -1;
    }

    memset(vis, 0, sizeof(vis));
    queue<Node> q;
    q.push((Node){0, 0, 0});
    vis[0][0][0] = true;

    // 小数据暴力：把时间显式写进状态，逐秒搜索。
    while (!q.empty()) {
        Node u = q.front();
        q.pop();

        if (danger_time[u.x][u.y] == INF) {
            return u.t;
        }

        if (u.t >= 75) {
            continue;
        }

        for (int i = 1; i <= 4; i++) {
            int nx = u.x + dx[i];
            int ny = u.y + dy[i];
            int nt = u.t + 1;

            if (!in_board(nx, ny)) {
                continue;
            }
            if (nt >= danger_time[nx][ny]) {
                continue;
            }
            if (vis[nx][ny][nt]) {
                continue;
            }

            vis[nx][ny][nt] = true;
            q.push((Node){nx, ny, nt});
        }
    }

    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> m;

    for (int i = 0; i < LIM; i++) {
        for (int j = 0; j < LIM; j++) {
            danger_time[i][j] = INF;
        }
    }

    for (int i = 1; i <= m; i++) {
        int x, y, t;
        cin >> x >> y >> t;

        for (int j = 0; j <= 4; j++) {
            int nx = x + dx[j];
            int ny = y + dy[j];
            if (!in_board(nx, ny)) {
                continue;
            }
            danger_time[nx][ny] = min(danger_time[nx][ny], t);
        }
    }

    cout << solve() << '\n';
    return 0;
}
