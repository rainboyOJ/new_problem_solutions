/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-11 00:38
 * update_at: 2026-11-11 00:38
 */
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cstring>

using namespace std;

const int INF = 0x3f3f3f3f;

int n, m, r, c;
int a[20][20];

// 记录当前选中的 r 行
int selected_rows[20];

// col_cost[j]: 单列 j 内部相邻行差绝对值和
int col_cost[20];

// pair_cost[i][j]: 相邻选列 i 和 j 之间各对应行差绝对值和
int pair_cost[20][20];

// dp[j][k]: 前 j 列选了 k 列且第 k 列选为第 j 列的最小分值
int dp[20][20];

int global_min_score = INF;

// 针对当前选定的行，进行列动态规划
void solve_dp() {
    // 预处理单列代价
    for (int j = 1; j <= m; ++j) {
        col_cost[j] = 0;
        for (int k = 1; k < r; ++k) {
            col_cost[j] += abs(a[selected_rows[k]][j] - a[selected_rows[k + 1]][j]);
        }
    }

    // 预处理两列横向代价
    for (int i = 1; i <= m; ++i) {
        for (int j = i + 1; j <= m; ++j) {
            pair_cost[i][j] = 0;
            for (int k = 1; k <= r; ++k) {
                pair_cost[i][j] += abs(a[selected_rows[k]][i] - a[selected_rows[k]][j]);
            }
        }
    }

    // 初始化 DP
    memset(dp, 0x3f, sizeof(dp));

    // 首列初始化（已选 1 列）
    for (int j = 1; j <= m; ++j) {
        dp[j][1] = col_cost[j];
    }

    // 递推选到第 k 列
    for (int k = 2; k <= c; ++k) {
        for (int j = k; j <= m; ++j) {
            for (int i = k - 1; i < j; ++i) {
                if (dp[i][k - 1] != INF) {
                    dp[j][k] = min(dp[j][k], dp[i][k - 1] + pair_cost[i][j] + col_cost[j]);
                }
            }
        }
    }

    for (int j = c; j <= m; ++j) {
        global_min_score = min(global_min_score, dp[j][c]);
    }
}

// DFS 枚举选哪 r 行
void dfs_rows(int cur_row, int chosen_cnt) {
    if (chosen_cnt == r) {
        solve_dp();
        return;
    }
    // 剪枝：剩余可选行不足
    if (cur_row > n || n - cur_row + 1 < r - chosen_cnt) {
        return;
    }

    // 选当前行
    selected_rows[chosen_cnt + 1] = cur_row;
    dfs_rows(cur_row + 1, chosen_cnt + 1);

    // 不选当前行
    dfs_rows(cur_row + 1, chosen_cnt);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> n >> m >> r >> c)) return 0;

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cin >> a[i][j];
        }
    }

    global_min_score = INF;
    dfs_rows(1, 0);

    cout << global_min_score << "\n";

    return 0;
}
