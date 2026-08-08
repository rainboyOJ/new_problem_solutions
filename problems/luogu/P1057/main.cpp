#include <bits/stdc++.h>
using namespace std;

const int MAXN = 35;

int n, m;
long long dp[MAXN][MAXN];

int left_pos(int x) {
    if (x == 1) {
        return n;
    }
    return x - 1;
}

int right_pos(int x) {
    if (x == n) {
        return 1;
    }
    return x + 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;

    // 传球开始前，球在 1 号同学手里。
    dp[0][1] = 1;

    for (int step = 1; step <= m; step++) {
        for (int pos = 1; pos <= n; pos++) {
            // 这一步结束后球在 pos，说明上一步球在它左右两边之一。
            dp[step][pos] = dp[step - 1][left_pos(pos)] + dp[step - 1][right_pos(pos)];
        }
    }

    cout << dp[m][1] << '\n';
    return 0;
}
