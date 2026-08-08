#include <bits/stdc++.h>
using namespace std;

int n, m;
string g[15];
int board[15][15];
int ans;

bool ok_place(int x, int y) {
    if (g[x][y] == 'H') {
        return false;
    }
    // 炮兵会攻击同一行或同一列上距离 1 或 2 的格子。
    int dx[8] = {0, 0, 0, 0, 1, -1, 2, -2};
    int dy[8] = {1, -1, 2, -2, 0, 0, 0, 0};
    for (int i = 0; i < 8; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (1 <= nx && nx <= n && 1 <= ny && ny <= m && board[nx][ny]) {
            return false;
        }
    }
    return true;
}

void dfs_cell(int pos, int used) {
    if (pos == n * m) {
        ans = max(ans, used);
        return;
    }

    int x = pos / m + 1;
    int y = pos % m + 1;

    dfs_cell(pos + 1, used);
    if (ok_place(x, y)) {
        board[x][y] = 1;
        dfs_cell(pos + 1, used + 1);
        board[x][y] = 0;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // brute.cpp：小数据逐格枚举是否放炮兵。
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> g[i];
        g[i] = " " + g[i];
    }
    memset(board, 0, sizeof(board));
    ans = 0;
    dfs_cell(0, 0);
    cout << ans << '\n';
    return 0;
}
