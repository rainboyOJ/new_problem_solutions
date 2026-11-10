/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-10 23:21
 * update_at: 2026-11-10 23:21
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

// 最大可能的连续面值在数百，定义足够大的数组上限
const int MAX_VAL = 2000;
const int INF = 0x3f3f3f3f;

int n, k;
int a[20];        // 当前搜索路径中的面值
int best_a[20];   // 最优面值方案
int best_max = 0; // 最大连续邮资

// dp[step][v] 表示前 step 种面值凑出面值 v 所需的最少邮票数
int dp[20][MAX_VAL + 5];

void dfs(int step, int cur_max) {
    if (step == k) {
        if (cur_max > best_max) {
            best_max = cur_max;
            for (int i = 1; i <= k; ++i) {
                best_a[i] = a[i];
            }
        }
        return;
    }

    // 枚举下一种面值：下界是 a[step] + 1，上界是 cur_max + 1
    for (int next_val = a[step] + 1; next_val <= cur_max + 1; ++next_val) {
        a[step + 1] = next_val;

        // 增量更新完全背包 DP
        for (int v = 0; v <= MAX_VAL; ++v) {
            dp[step + 1][v] = dp[step][v];
            if (v >= next_val) {
                dp[step + 1][v] = min(dp[step + 1][v], dp[step + 1][v - next_val] + 1);
            }
        }

        // 寻找新的连续邮资上限
        int next_max = cur_max;
        while (next_max + 1 <= MAX_VAL && dp[step + 1][next_max + 1] <= n) {
            next_max++;
        }

        dfs(step + 1, next_max);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> n >> k)) return 0;

    // 初始化第一种面值必为 1
    a[1] = 1;
    memset(dp, 0x3f, sizeof(dp));
    dp[1][0] = 0;
    for (int v = 1; v <= n; ++v) {
        dp[1][v] = v;
    }

    // 只有面值 1 时，最多贴 n 张，能连续贴出的最大邮资为 n
    dfs(1, n);

    for (int i = 1; i <= k; ++i) {
        cout << best_a[i] << (i == k ? "" : " ");
    }
    cout << "\n";
    cout << "MAX=" << best_max << "\n";

    return 0;
}
