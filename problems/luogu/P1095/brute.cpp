/**
 * Problem: luogu P1095 - [NOIP 2007 普及组] 守望者的逃离 (Brute DP)
 * Author: rainboy
 * Date: 2026-11-10 23:00
 * Description: 二维记忆化/动态规划对拍基准
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

// 暴力定义：dp[i][m] 表示第 i 秒魔法值为 m 时所能到达的最大距离
// 由于魔力初始可达 1000，且中途最多 1000 + 4 * 300000，但超过某个阈值继续增加已无意义
// 为了作为可靠且通用的对拍器，我们使用滚动数组严格维护 dp[m] = 最大距离
const int INF = 1e9;
const int MAXM = 1050; // 魔力上限截断（超过1000等价于很多次闪烁）

int dp[MAXM];
int next_dp[MAXM];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m, s, t;
    if (!(cin >> m >> s >> t)) return 0;

    int max_m = max(m, 1000);
    for (int j = 0; j <= max_m; ++j) {
        dp[j] = -INF;
    }
    dp[m] = 0;

    for (int sec = 1; sec <= t; ++sec) {
        for (int j = 0; j <= max_m; ++j) {
            next_dp[j] = -INF;
        }

        for (int j = 0; j <= max_m; ++j) {
            if (dp[j] < 0) continue;

            // 1. 跑步：魔法不变，距离 + 17
            next_dp[j] = max(next_dp[j], dp[j] + 17);

            // 2. 休息：魔法 + 4，距离不变
            int nm = min(max_m, j + 4);
            next_dp[nm] = max(next_dp[nm], dp[j]);

            // 3. 闪烁：魔法 >= 10 时消耗 10，距离 + 60
            if (j >= 10) {
                next_dp[j - 10] = max(next_dp[j - 10], dp[j] + 60);
            }
        }

        int cur_max = 0;
        for (int j = 0; j <= max_m; ++j) {
            dp[j] = next_dp[j];
            cur_max = max(cur_max, dp[j]);
        }

        if (cur_max >= s) {
            cout << "Yes\n" << sec << "\n";
            return 0;
        }
    }

    int ans = 0;
    for (int j = 0; j <= max_m; ++j) {
        ans = max(ans, dp[j]);
    }
    cout << "No\n" << ans << "\n";

    return 0;
}
