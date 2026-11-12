/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-12 14:59
 * update_at: 2026-11-12 14:59
 */
#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

const int MOD = 1e9 + 7;

// dp[mask] 表示当前为止，所有元素按位与（AND）结果恰好等于 mask 的非空子序列方案数
int dp[64];
int new_dp[64];

void solve() {
    int n, k;
    if (!(cin >> n >> k)) return;

    // 清空状态桶
    memset(dp, 0, sizeof(dp));

    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;

        // 双缓冲备份：保留不选当前数 x 的历史所有方案
        for (int mask = 0; mask < 64; ++mask) {
            new_dp[mask] = dp[mask];
        }

        // 1. 自身单独成段：x 自己构成长度为 1 的子序列，与和为 x
        new_dp[x] = (new_dp[x] + 1) % MOD;

        // 2. 拼接贡献：将 x 接在已有子序列后面，按位与后坍缩至 new_mask = mask & x
        for (int mask = 0; mask < 64; ++mask) {
            if (dp[mask] == 0) continue;
            int nxt = mask & x;
            new_dp[nxt] = (new_dp[nxt] + dp[mask]) % MOD;
        }

        // 更新状态桶
        for (int mask = 0; mask < 64; ++mask) {
            dp[mask] = new_dp[mask];
        }
    }

    // 统计所有二进制中 1 的个数恰好为 k 的子序列总数
    int ans = 0;
    for (int mask = 0; mask < 64; ++mask) {
        if (__builtin_popcount(mask) == k) {
            ans = (ans + dp[mask]) % MOD;
        }
    }

    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    return 0;
}
