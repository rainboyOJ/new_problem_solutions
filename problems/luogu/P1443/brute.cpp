#include <bits/stdc++.h>
using namespace std;

const int MAXN = 35;

int n, m, sx, sy;
int ans[MAXN][MAXN];
int dx[8] = {-2, -2, -1, -1, 1, 1, 2, 2};
int dy[8] = {-1, 1, -2, 2, -2, 2, -1, 1};

struct Node {
    int x;
    int y;
};

bool in_board(int x, int y) {
    return x >= 1 && x <= n && y >= 1 && y <= m;
}

int single_bfs(int tx, int ty) {
    static int dista[MAXN][MAXN];
    memset(dista, -1, sizeof(dista));

    queue<Node> q;
    dista[sx][sy] = 0;
    q.push((Node){sx, sy});

    while (!q.empty()) {
        Node u = q.front();
        q.pop();

        if (u.x == tx && u.y == ty) {
            return dista[tx][ty];
        }

        for (int i = 0; i < 8; i++) {
            int nx = u.x + dx[i];
            int ny = u.y + dy[i];

            if (!in_board(nx, ny)) {
                continue;
            }
            if (dista[nx][ny] != -1) {
                continue;
            }

            dista[nx][ny] = dista[u.x][u.y] + 1;
            q.push((Node){nx, ny});
        }
    }

    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> sx >> sy;

    // 朴素做法：对每个格子都单独跑一次 BFS。
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            ans[i][j] = single_bfs(i, j);
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (j > 1) {
                cout << ' ';
            }
            cout << ans[i][j];
        }
        cout << '\n';
    }

    return 0;
}
