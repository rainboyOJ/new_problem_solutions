#include <bits/stdc++.h>
using namespace std;

const int MAXN = 15;

int n;
char g[MAXN][MAXN];
int x1_pos, y1_pos, x2_pos, y2_pos;
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};
bool vis[MAXN][MAXN];
int ans = 1e9;

bool in_board(int x, int y) {
    return x >= 1 && x <= n && y >= 1 && y <= n;
}

void dfs(int x, int y, int step) {
    if (step >= ans) {
        return;
    }
    if (x == x2_pos && y == y2_pos) {
        ans = step;
        return;
    }

    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];

        if (!in_board(nx, ny)) {
            continue;
        }
        if (g[nx][ny] == '1') {
            continue;
        }
        if (vis[nx][ny]) {
            continue;
        }

        vis[nx][ny] = true;
        dfs(nx, ny, step + 1);
        vis[nx][ny] = false;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> (g[i] + 1);
    }
    cin >> x1_pos >> y1_pos >> x2_pos >> y2_pos;

    // 小数据暴力：枚举所有不重复路径，并用当前最优答案剪枝。
    vis[x1_pos][y1_pos] = true;
    dfs(x1_pos, y1_pos, 0);

    if (ans == (int) 1e9) {
        cout << -1 << '\n';
    }
    else {
        cout << ans << '\n';
    }
    return 0;
}
