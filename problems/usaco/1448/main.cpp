/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 20:48
 * update_at: 2026-07-11 20:54
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;
const int MAXQ = 200005;

int n, q;
int dir_grid[MAXN][MAXN]; // -1 表示 ?，0/1/2/3 分别表示 L/R/U/D。
bool good[MAXN][MAXN];    // good[i][j] 表示从这个格子出发可以离开网格。
int rr[MAXQ], cc[MAXQ], tt[MAXQ];
int ans[MAXQ];
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

// 判断当前状态下，格子 (x,y) 是否已经能成为 good。
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

// 如果 (x,y) 可以变成 good，就把它加入队列并向反方向扩展。
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
        char ch;
        cin >> rr[i] >> cc[i] >> ch;
        tt[i] = get_dir(ch);
        dir_grid[rr[i]][cc[i]] = tt[i];
    }

    // 先在最终状态下找出所有能离开网格的格子。
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            try_add(i, j);
        }
    }

    // 倒着撤销传送带。撤销只会让 good 集合变大，不会让它变小。
    for (int day = q; day >= 1; day--) {
        ans[day] = n * n - cur_good;
        dir_grid[rr[day]][cc[day]] = -1;
        try_add(rr[day], cc[day]);
    }

    for (int i = 1; i <= q; i++) {
        cout << ans[i] << '\n';
    }

    return 0;
}
