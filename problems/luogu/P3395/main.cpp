#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000 + 5;
const int INF = 0x3f3f3f3f;

int T;
int n;
int block_time[MAXN][MAXN];
int dista[MAXN][MAXN];
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

struct Node {
    int x;
    int y;
};

bool in_board(int x, int y) {
    return x >= 1 && x <= n && y >= 1 && y <= n;
}

bool can_enter(int x, int y, int t) {
    // 普通格子要求在路障放下之前进入。
    if (x == n && y == n) {
        return t <= block_time[x][y];
    }
    return t < block_time[x][y];
}

bool bfs() {
    queue<Node> q;
    memset(dista, -1, sizeof(dista));

    dista[1][1] = 0;
    q.push((Node){1, 1});

    while (!q.empty()) {
        Node u = q.front();
        q.pop();

        if (u.x == n && u.y == n) {
            return true;
        }

        for (int i = 0; i < 4; i++) {
            int nx = u.x + dx[i];
            int ny = u.y + dy[i];
            int nt = dista[u.x][u.y] + 1;

            if (!in_board(nx, ny)) {
                continue;
            }
            if (dista[nx][ny] != -1) {
                continue;
            }
            if (!can_enter(nx, ny, nt)) {
                continue;
            }

            dista[nx][ny] = nt;
            q.push((Node){nx, ny});
        }
    }

    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> T;
    while (T--) {
        cin >> n;

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                block_time[i][j] = INF;
            }
        }

        for (int i = 1; i <= 2 * n - 2; i++) {
            int x, y;
            cin >> x >> y;
            block_time[x][y] = min(block_time[x][y], i);
        }

        if (n == 1) {
            cout << "Yes\n";
            continue;
        }

        cout << (bfs() ? "Yes" : "No") << '\n';
    }

    return 0;
}
