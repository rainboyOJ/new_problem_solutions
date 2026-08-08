// brute.cpp：小数据直接 BFS 找一条路，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXR = 120;
const int MAXC = 80;

int r, c;
char g[MAXR][MAXC];
int vis[MAXR][MAXC];
int pre_x[MAXR][MAXC], pre_y[MAXR][MAXC];
int qx[MAXR * MAXC], qy[MAXR * MAXC];
int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};

bool in_board(int x, int y) {
    return x >= 1 && x <= r && y >= 1 && y <= c;
}

void bfs() {
    memset(vis, 0, sizeof(vis));
    int head = 0, tail = 0;

    qx[tail] = 1;
    qy[tail] = 1;
    tail++;
    vis[1][1] = 1;
    pre_x[1][1] = 0;
    pre_y[1][1] = 0;

    while (head < tail) {
        int x = qx[head];
        int y = qy[head];
        head++;

        if (x == r && y == c) {
            return;
        }

        for (int k = 0; k < 4; k++) {
            int nx = x + dx[k];
            int ny = y + dy[k];
            if (!in_board(nx, ny)) {
                continue;
            }
            if (g[nx][ny] == '*') {
                continue;
            }
            if (vis[nx][ny]) {
                continue;
            }

            vis[nx][ny] = 1;
            pre_x[nx][ny] = x;
            pre_y[nx][ny] = y;
            qx[tail] = nx;
            qy[tail] = ny;
            tail++;
        }
    }
}

void print_path() {
    vector<pair<int, int> > path;
    int x = r, y = c;
    while (x != 0 && y != 0) {
        path.push_back(make_pair(x, y));
        int px = pre_x[x][y];
        int py = pre_y[x][y];
        x = px;
        y = py;
    }

    reverse(path.begin(), path.end());
    for (int i = 0; i < (int) path.size(); i++) {
        cout << path[i].first << ' ' << path[i].second << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> r >> c;
    for (int i = 1; i <= r; i++) {
        for (int j = 1; j <= c; j++) {
            cin >> g[i][j];
        }
    }

    bfs();
    print_path();

    return 0;
}
