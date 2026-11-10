/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-11 02:05
 * update_at: 2026-11-11 02:05
 */

// brute.cpp：小数据 vector 模拟基线
#include <iostream>
#include <vector>

using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, q;
    if (!(cin >> n >> m >> q)) return 0;

    vector<vector<ll>> grid(n + 1, vector<ll>(m + 1));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            grid[i][j] = 1LL * (i - 1) * m + j;
        }
    }

    while (q--) {
        int x, y;
        cin >> x >> y;
        ll ans = grid[x][y];
        cout << ans << "\n";

        // 向左看齐
        for (int j = y; j < m; ++j) {
            grid[x][j] = grid[x][j + 1];
        }

        // 最后一列向上看齐
        ll temp = ans;
        for (int i = x; i < n; ++i) {
            grid[i][m] = grid[i + 1][m];
        }
        grid[n][m] = temp;
    }

    return 0;
}
