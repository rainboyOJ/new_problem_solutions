/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-10 21:46
 * update_at: 2026-10-21 14:35
 */
// brute.cpp：小数据暴力解，用状态压缩 DP 直接模拟购买顺序，用来独立验证 main.cpp。
// 状态 mask 表示"已经买了哪些礼物"。转移时选一件未买的 j，
// 代价取「直接买 A」与「从已买的某件 i 用优惠价买 K[i][j]」的最小值。
//
// 关键细节：K[i][j] == 0 表示这两件礼物之间没有优惠，不是免费的边。
// 若把 0 也拿去取 min，会误以为可以免费连锁购买（例如 3 件礼物、全 0 矩阵时
// 会算出 3 而不是正确的 9）。
//
// 与 main.cpp 的最小生成树建模完全不共享实现，因此适合用来独立验证。
// 状态数 2^B，只在 B 很小时可用。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 12;  // 只枚举极小数据：B <= 8 较稳妥
const int INF = 1e9;

int direct_cost;  // 直接买任意一件礼物的价格 A
int gift_cnt;     // 礼物数量 B
int discount[MAXN][MAXN];  // discount[i][j]：已买 i 后买 j 的优惠价，0 表示无优惠

int dp[1 << MAXN];  // dp[mask]：买齐 mask 中这些礼物的最小花费

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> direct_cost >> gift_cnt;
    for (int i = 0; i < gift_cnt; i++) {
        for (int j = 0; j < gift_cnt; j++) {
            cin >> discount[i][j];
        }
    }

    int max_mask = 1 << gift_cnt;
    for (int i = 0; i < max_mask; i++) {
        dp[i] = INF;
    }
    dp[0] = 0;

    for (int mask = 0; mask < max_mask; mask++) {
        if (dp[mask] == INF) continue;

        for (int j = 0; j < gift_cnt; j++) {
            if ((mask >> j) & 1) continue;  // 已经买过

            // 直接买
            int cost = direct_cost;
            // 或者用某件已买礼物的优惠价
            for (int i = 0; i < gift_cnt; i++) {
                if (((mask >> i) & 1) == 0) continue;  // i 还没买，用不上它的优惠
                if (discount[i][j] == 0) continue;      // 0 表示没有优惠，不是免费
                cost = min(cost, discount[i][j]);
            }

            int next_mask = mask | (1 << j);
            dp[next_mask] = min(dp[next_mask], dp[mask] + cost);
        }
    }

    cout << dp[max_mask - 1] << '\n';
    return 0;
}
