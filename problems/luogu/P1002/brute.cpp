#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int n, m, hx, hy;
ll ans = 0;
bool blocked[30][30];

int dx[] = {0, 1, 1, -1, -1, 2, 2, -2, -2};
int dy[] = {0, 2, -2, 2, -2, 1, -1, 1, -1};

bool in_board(int x, int y) {
    return x >= 0 && x <= n && y >= 0 && y <= m;
}

void mark_horse() {
    for (int i = 0; i < 9; i++) {
        int nx = hx + dx[i];
        int ny = hy + dy[i];
        if (in_board(nx, ny)) {
            blocked[nx][ny] = true;
        }
    }
}

// 枚举所有路径：每一步向下或向右
void dfs(int x, int y) {
    if (x == n && y == m) {
        ans++;
        return;
    }
    // 向下走
    if (x + 1 <= n && !blocked[x + 1][y]) {
        dfs(x + 1, y);
    }
    // 向右走
    if (y + 1 <= m && !blocked[x][y + 1]) {
        dfs(x, y + 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> hx >> hy;
    mark_horse();
    if (!blocked[0][0]) {
        dfs(0, 0);
    }
    cout << ans << '\n';
    return 0;
}
