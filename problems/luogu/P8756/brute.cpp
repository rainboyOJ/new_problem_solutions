#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;

int n, m, k_need;
int board[10][105];
long long ans;
int dx[8] = {-2, -2, -1, -1, 1, 1, 2, 2};
int dy[8] = {-1, 1, -2, 2, -2, 2, -1, 1};

bool ok_place(int x, int y) {
    for (int i = 0; i < 8; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx >= 1 && nx <= n && ny >= 1 && ny <= m && board[nx][ny]) {
            return false;
        }
    }
    return true;
}

void dfs_cell(int pos, int used) {
    if (used > k_need) {
        return;
    }
    if (pos == n * m) {
        if (used == k_need) {
            ans++;
        }
        return;
    }

    int x = pos % n + 1;
    int y = pos / n + 1;

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

    // brute.cpp：小数据直接枚举每个格子放不放马。
    cin >> n >> m >> k_need;
    memset(board, 0, sizeof(board));
    ans = 0;
    dfs_cell(0, 0);
    cout << ans % MOD << '\n';
    return 0;
}
