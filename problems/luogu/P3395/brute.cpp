#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10;
const int INF = 0x3f3f3f3f;

int T;
int n;
int block_time[MAXN][MAXN];
bool vis[MAXN][MAXN][105];
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

struct Node {
    int x;
    int y;
    int t;
};

bool in_board(int x, int y) {
    return x >= 1 && x <= n && y >= 1 && y <= n;
}

bool can_enter(int x, int y, int t) {
    if (x == n && y == n) {
        return t <= block_time[x][y];
    }
    return t < block_time[x][y];
}

bool solve_one() {
    if (n == 1) {
        return true;
    }

    memset(vis, 0, sizeof(vis));
    queue<Node> q;
    q.push((Node){1, 1, 0});
    vis[1][1][0] = true;

    // 小数据暴力：显式把“时间”放进状态里，逐秒搜索。
    while (!q.empty()) {
        Node u = q.front();
        q.pop();

        if (u.x == n && u.y == n) {
            return true;
        }

        if (u.t >= 100) {
            continue;
        }

        for (int i = 0; i < 4; i++) {
            int nx = u.x + dx[i];
            int ny = u.y + dy[i];
            int nt = u.t + 1;

            if (!in_board(nx, ny)) {
                continue;
            }
            if (!can_enter(nx, ny, nt)) {
                continue;
            }
            if (vis[nx][ny][nt]) {
                continue;
            }

            vis[nx][ny][nt] = true;
            q.push((Node){nx, ny, nt});
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

        cout << (solve_one() ? "Yes" : "No") << '\n';
    }

    return 0;
}
