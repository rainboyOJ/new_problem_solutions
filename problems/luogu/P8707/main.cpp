#include <bits/stdc++.h>
using namespace std;

const int MAXN = 35;

int n, m;
long long dp[MAXN][MAXN]; // dp[i][j] 表示走到 (i,j) 的方案数

bool blocked(int x, int y) {
    return x % 2 == 0 && y % 2 == 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;

    if (blocked(1, 1)) {
        cout << 0 << '\n';
        return 0;
    }

    dp[1][1] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (i == 1 && j == 1) {
                continue;
            }
            if (blocked(i, j)) {
                dp[i][j] = 0;
                continue;
            }
            dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
        }
    }

    cout << dp[n][m] << '\n';
    return 0;
}
