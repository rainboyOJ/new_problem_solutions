/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 20:48
 * update_at: 2026-07-11 20:54
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;

int n, q;
int dir_grid[MAXN][MAXN]; // -1 表示 ?，0/1/2/3 分别表示 L/R/U/D。
bool good[MAXN][MAXN];
int cur_good;

int dx[4] = {0, 0, -1, 1};
int dy[4] = {-1, 1, 0, 0};

queue<pair<int, int> > que;

int get_dir(char ch) {
    if (ch == 'L') return 0;
    if (ch == 'R') return 1;
    if (ch == 'U') return 2;
    return 3;
}

bool inside(int x, int y) {
    return x >= 1 && x <= n && y >= 1 && y <= n;
}

bool can_be_good(int x, int y) {
    if (!inside(x, y)) return false;

    for (int d = 0; d < 4; d++) {
        if (dir_grid[x][y] != -1 && dir_grid[x][y] != d) continue;

        int nx = x + dx[d];
        int ny = y + dy[d];
        if (!inside(nx, ny) || good[nx][ny]) {
            return true;
        }
    }
    return false;
}

void try_add(int x, int y) {
    if (!inside(x, y)) return;
    if (good[x][y]) return;
    if (!can_be_good(x, y)) return;

    good[x][y] = true;
    cur_good++;
    que.push(make_pair(x, y));

    while (!que.empty()) {
        int now_x = que.front().first;
        int now_y = que.front().second;
        que.pop();

        for (int d = 0; d < 4; d++) {
            int nx = now_x + dx[d];
            int ny = now_y + dy[d];
            if (!inside(nx, ny)) continue;
            if (good[nx][ny]) continue;
            if (!can_be_good(nx, ny)) continue;

            good[nx][ny] = true;
            cur_good++;
            que.push(make_pair(nx, ny));
        }
    }
}

int calc_bad() {
    cur_good = 0;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            good[i][j] = false;
        }
    }

    // 暴力做法：每次更新后，从头重新扩展所有 good 格子。
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            try_add(i, j);
        }
    }

    return n * n - cur_good;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            dir_grid[i][j] = -1;
        }
    }

    for (int i = 1; i <= q; i++) {
        int r, c;
        char ch;
        cin >> r >> c >> ch;
        dir_grid[r][c] = get_dir(ch);
        cout << calc_bad() << '\n';
    }

    return 0;
}
