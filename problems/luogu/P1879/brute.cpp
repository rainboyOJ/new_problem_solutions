#include <bits/stdc++.h>
using namespace std;

const int MOD = 100000000;

int n, m;
int a[15][15];
int used[15][15];
int ans;

bool ok_place(int x, int y) {
    if (a[x][y] == 0) {
        return false;
    }
    if (y > 1 && used[x][y - 1]) {
        return false;
    }
    if (x > 1 && used[x - 1][y]) {
        return false;
    }
    return true;
}

void dfs_cell(int pos) {
    if (pos == n * m) {
        ans++;
        if (ans >= MOD) {
            ans -= MOD;
        }
        return;
    }

    int x = pos / m + 1;
    int y = pos % m + 1;

    // 不在这个格子种草。
    dfs_cell(pos + 1);

    // 在这个格子种草。
    if (ok_place(x, y)) {
        used[x][y] = 1;
        dfs_cell(pos + 1);
        used[x][y] = 0;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // brute.cpp：逐格枚举种或不种，用来帮助理解题意和辅助对拍。
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> a[i][j];
        }
    }

    memset(used, 0, sizeof(used));
    ans = 0;
    dfs_cell(0);
    cout << ans << '\n';
    return 0;
}
