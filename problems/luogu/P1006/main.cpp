/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-10 22:47
 * update_at: 2026-11-10 22:47
 */
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

// m 行 n 列，点权存储在 a 数组中
int m, n;
int a[55][55];

// dp[s][i][j] 表示两人同步走，当前坐标和为 s = x + y 时，
// 第一个人的行号为 i，第二个人的行号为 j 时的最大权值和。
// 约定 i < j 避免两路径相交重复选取点（除起点和终点外）。
int dp[110][55][55];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> m >> n)) return 0;

    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            cin >> a[i][j];
        }
    }

    // 步数驱动：s 表示两人的 (x + y)，从 3 到 m + n
    // 起点 (1, 1) 的 x + y = 2
    // 第一步离开起点后到达 s = 3，可能的位置是 (1, 2) 和 (2, 1)
    for (int s = 3; s <= m + n; ++s) {
        for (int i = 1; i <= m; ++i) {
            int y1 = s - i;
            if (y1 < 1 || y1 > n) continue;

            for (int j = i + 1; j <= m; ++j) {
                int y2 = s - j;
                if (y2 < 1 || y2 > n) continue;

                // 上一步四种转移取最大值
                int prev_max = dp[s - 1][i][j];             // 两人都从左边来 (y-1)
                prev_max = max(prev_max, dp[s - 1][i - 1][j]);     // 1从上来，2从左来
                prev_max = max(prev_max, dp[s - 1][i][j - 1]);     // 1从左来，2从上来
                prev_max = max(prev_max, dp[s - 1][i - 1][j - 1]); // 两人都从上来

                dp[s][i][j] = prev_max + a[i][y1] + a[j][y2];
            }
        }
    }

    // 最终汇聚在 (m, n)，即前一步落在 (m-1, n) 和 (m, n-1)
    // 此时 s = m + n - 1，行号分别为 m - 1 和 m
    // 终点 (m, n) 的权值为 0，直接输出该状态的最大值即可
    cout << dp[m + n - 1][m - 1][m] << "\n";

    return 0;
}
