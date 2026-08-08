#include <bits/stdc++.h>
using namespace std;

const int MAXN = 705;
const int MAXQ = 500000 + 5;

int n, m;
int h[MAXN][MAXN];
int vis[MAXN][MAXN];          // 是否已经归入某个平台
int qx[MAXQ], qy[MAXQ];
int dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
int dy[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

bool in_board(int x, int y) {
    return x >= 1 && x <= n && y >= 1 && y <= m;
}

bool bfs_component(int sx, int sy) {
    int head = 0, tail = 0;
    int height = h[sx][sy];
    bool is_peak = true;

    qx[tail] = sx;
    qy[tail] = sy;
    tail++;
    vis[sx][sy] = 1;

    while (head < tail) {
        int x = qx[head];
        int y = qy[head];
        head++;

        for (int k = 0; k < 8; k++) {
            int nx = x + dx[k];
            int ny = y + dy[k];
            if (!in_board(nx, ny)) {
                continue;
            }
            if (h[nx][ny] > height) {
                is_peak = false;
            }
            if (h[nx][ny] == height && !vis[nx][ny]) {
                vis[nx][ny] = 1;
                qx[tail] = nx;
                qy[tail] = ny;
                tail++;
            }
        }
    }

    return is_peak;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> h[i][j];
        }
    }

    memset(vis, 0, sizeof(vis));
    int ans = 0;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (vis[i][j]) {
                continue;
            }
            if (bfs_component(i, j)) {
                ans++;
            }
        }
    }

    cout << ans << '\n';
    return 0;
}
