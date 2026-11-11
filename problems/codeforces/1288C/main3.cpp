#include <iostream>
#include <vector>

using namespace std;

const int MOD = 1e9 + 7;

// f[pos][v] 表示长度为 pos、末尾为 v 的非降序列 (a) 方案数
int f_dp[15][1005];
// g[pos][v] 表示长度为 pos、末尾为 v 的非增序列 (b) 方案数
int g_dp[15][1005];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    // pos = 1 初始化
    for (int v = 1; v <= n; ++v) {
        f_dp[1][v] = 1;
        g_dp[1][v] = 1;
    }

    // 递推计算长度从 2 到 m
    for (int pos = 2; pos <= m; ++pos) {
        // a 序列非降：f[pos][v] = sum_{u=1}^v f[pos-1][u]
        long long sum_f = 0;
        for (int v = 1; v <= n; ++v) {
            sum_f = (sum_f + f_dp[pos - 1][v]) % MOD;
            f_dp[pos][v] = sum_f;
        }

        // b 序列非增：g[pos][v] = sum_{u=v}^n g[pos-1][u]
        long long sum_g = 0;
        for (int v = n; v >= 1; --v) {
            sum_g = (sum_g + g_dp[pos - 1][v]) % MOD;
            g_dp[pos][v] = sum_g;
        }
    }

    // 统计答案：只要末尾满足 a_m <= b_m，中间所有约束自动成立
    long long ans = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = i; j <= n; ++j) {
            long long cur = 1LL * f_dp[m][i] * g_dp[m][j] % MOD;
            ans = (ans + cur) % MOD;
        }
    }

    cout << ans << "\n";
    return 0;
}
