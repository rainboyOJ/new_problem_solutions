#include <bits/stdc++.h>
using namespace std;

const int MAXN = 30005;

int n, m;
// dp[j] 表示花费 j 元能获得的最大价值（价格 × 重要度）。
int dp[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;

    for (int i = 1; i <= m; i++) {
        int v, p;
        cin >> v >> p;
        int w = v * p;                   // 价值 = 价格 × 重要度
        // 0/1 背包倒序枚举。
        for (int j = n; j >= v; j--) {
            dp[j] = max(dp[j], dp[j - v] + w);
        }
    }

    cout << dp[n] << '\n';
    return 0;
}
