#include <bits/stdc++.h>
using namespace std;

const int MAXC = 10005;

int v_target, n, c;
// dp[j] 表示花费 j 体力能填的最大体积。
int dp[MAXC];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> v_target >> n >> c;

    fill(dp, dp + c + 1, 0);

    // 0/1 背包：体力是容量，石头体积是价值。
    for (int i = 1; i <= n; i++) {
        int k, m;
        cin >> k >> m;
        for (int j = c; j >= m; j--) {
            dp[j] = max(dp[j], dp[j - m] + k);
        }
    }

    // 找到最小的体力花费使填的体积 ≥ 目标。
    for (int j = 0; j <= c; j++) {
        if (dp[j] >= v_target) {
            cout << c - j << '\n';       // 剩余体力
            return 0;
        }
    }

    cout << "Impossible" << '\n';
    return 0;
}
