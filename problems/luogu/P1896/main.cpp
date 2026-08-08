/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * date: 2026-07-07 00:00:00
 */
// main.cpp：状态压缩 DP，逐行转移。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10;
const int MAXK = 85;
const int MAXS = 1 << 9;  // N ≤ 9

int n, k;
long long dp[MAXN][MAXS][MAXK];  // dp[row][mask][cnt]

// valid_one[mask] = 1 表示 mask 中没有任何相邻的 1
int valid_one[MAXS];
// king_cnt[mask] = mask 中 1 的个数
int king_cnt[MAXS];
// valid_sets 保存所有合法的单行状态
vector<int> valid_sets;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;

    // 预处理所有合法的单行状态
    for (int mask = 0; mask < (1 << n); mask++) {
        if (mask & (mask << 1)) continue;  // 同一行有相邻国王
        valid_one[mask] = 1;
        king_cnt[mask] = __builtin_popcount(mask);
        valid_sets.push_back(mask);
    }

    // 第 1 行初始化
    for (int mask : valid_sets) {
        if (king_cnt[mask] <= k) {
            dp[1][mask][king_cnt[mask]] = 1;
        }
    }

    // 逐行 DP
    for (int row = 2; row <= n; row++) {
        for (int cur : valid_sets) {
            int cnt_cur = king_cnt[cur];
            if (cnt_cur > k) continue;

            for (int prev : valid_sets) {
                // 检查上下行冲突
                if ((cur & prev) || ((cur << 1) & prev) || ((cur >> 1) & prev)) continue;

                for (int c = cnt_cur; c <= k; c++) {
                    dp[row][cur][c] += dp[row - 1][prev][c - cnt_cur];
                }
            }
        }
    }

    // 汇总答案
    long long ans = 0;
    for (int mask : valid_sets) {
        ans += dp[n][mask][k];
    }

    cout << ans << '\n';
    return 0;
}
