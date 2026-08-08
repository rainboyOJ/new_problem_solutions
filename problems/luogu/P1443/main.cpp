#include <bits/stdc++.h>
using namespace std;

const int MAXN = 405;

int n, m, sx, sy;
int dista[MAXN][MAXN];
int dx[8] = {-2, -2, -1, -1, 1, 1, 2, 2};
int dy[8] = {-1, 1, -2, 2, -2, 2, -1, 1};

struct Node {
    int x;
    int y;
};

bool in_board(int x, int y) {
    return x >= 1 && x <= n && y >= 1 && y <= m;
}

void bfs() {
    queue<Node> q;
    dista[sx][sy] = 0;
    q.push((Node){sx, sy});

    while (!q.empty()) {
        Node u = q.front();
        q.pop();

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
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> sx >> sy;

    memset(dista, -1, sizeof(dista));
    bfs();

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (j > 1) {
                cout << ' ';
            }
            cout << dista[i][j];
        }
        cout << '\n';
    }

    return 0;
}
