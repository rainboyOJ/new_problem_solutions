/**
 * Problem: luogu P2540 - [NOIP 2015 提高组] 斗地主 加强版
 * Author: rainboy
 * Date: 2026-11-11 00:40
 * Description: 散牌五维预处理 DP + 顺子回溯 DFS
 */
#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

const int INF = 0x3f3f3f3f;

int t, n;
int p[20];
int dp[24][24][24][24][3];
int cnt_stat[10];
int st_len[4] = {0, 5, 3, 2}; // 1: 单顺子>=5, 2: 双顺子>=3, 3: 三顺子>=2
int ans;

void init_dp() {
    memset(dp, 0x3f, sizeof(dp));
    dp[0][0][0][0][0] = 0;

    for (int d = 0; d <= 15; ++d) {
        for (int c = 0; c <= 15; ++c) {
            for (int b = 0; b <= 15; ++b) {
                for (int a = 0; a <= 15; ++a) {
                    for (int e = 0; e <= 2; ++e) {
                        int minn = dp[a][b][c][d][e];

                        // 单牌、对子、三张、炸弹单出
                        if (a > 0) minn = min(minn, dp[a - 1][b][c][d][e] + 1);
                        if (b > 0) minn = min(minn, dp[a][b - 1][c][d][e] + 1);
                        if (c > 0) minn = min(minn, dp[a][b][c - 1][d][e] + 1);
                        if (d > 0) minn = min(minn, dp[a][b][c][d - 1][e] + 1);
                        if (e > 0) minn = min(minn, dp[a][b][c][d][e - 1] + 1);

                        // 三带一
                        if (c > 0 && a > 0) minn = min(minn, dp[a - 1][b][c - 1][d][e] + 1);
                        if (c > 0 && e > 0) minn = min(minn, dp[a][b][c - 1][d][e - 1] + 1);
                        // 三带二
                        if (c > 0 && b > 0) minn = min(minn, dp[a][b - 1][c - 1][d][e] + 1);

                        // 四带二单
                        if (d > 0 && a >= 2) minn = min(minn, dp[a - 2][b][c][d - 1][e] + 1);
                        if (d > 0 && a >= 1 && e >= 1) minn = min(minn, dp[a - 1][b][c][d - 1][e - 1] + 1);
                        if (d > 0 && e >= 2) minn = min(minn, dp[a][b][c][d - 1][e - 2] + 1);
                        if (d > 0 && b >= 1) minn = min(minn, dp[a][b - 1][c][d - 1][e] + 1); // 拆对当两单
                        // 四带二对
                        if (d > 0 && b >= 2) minn = min(minn, dp[a][b - 2][c][d - 1][e] + 1);
                        if (d >= 2) minn = min(minn, dp[a][b][c][d - 2][e] + 1); // 两个炸弹互相带

                        // 拆牌转移（不计步数）
                        if (c > 0) minn = min(minn, dp[a + 1][b + 1][c - 1][d][e]);
                        if (d > 0) minn = min(minn, dp[a + 1][b][c + 1][d - 1][e]);
                        if (e >= 2) minn = min(minn, dp[a][b][c][d][e - 2] + 1); // 两张王直接出

                        dp[a][b][c][d][e] = minn;
                    }
                }
            }
        }
    }
}

void dfs(int step) {
    if (step >= ans) return;

    // 枚举顺子
    for (int k = 1; k <= 3; ++k) {
        for (int i = 1; i <= 12; ++i) {
            int l = 0;
            while (i + l <= 12 && p[i + l] >= k) l++;
            for (int j = l; j >= st_len[k]; j--) {
                for (int t = i; t <= i + j - 1; ++t) p[t] -= k;
                dfs(step + 1);
                for (int t = i; t <= i + j - 1; ++t) p[t] += k;
            }
        }
    }

    // 统计剩余散牌状态
    memset(cnt_stat, 0, sizeof(cnt_stat));
    for (int i = 1; i <= 13; ++i) {
        if (p[i] >= 1 && p[i] <= 4) {
            cnt_stat[p[i]]++;
        }
    }
    int king_cnt = p[14];

    ans = min(ans, step + dp[cnt_stat[1]][cnt_stat[2]][cnt_stat[3]][cnt_stat[4]][king_cnt]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    init_dp();

    if (!(cin >> t >> n)) return 0;
    while (t--) {
        ans = n;
        memset(p, 0, sizeof(p));
        for (int i = 1; i <= n; ++i) {
            int rank_val, suit_val;
            cin >> rank_val >> suit_val;
            if (rank_val == 0) {
                p[14]++; // 王
            } else if (rank_val == 1) {
                p[12]++; // A 映射为 12
            } else if (rank_val == 2) {
                p[13]++; // 2 映射为 13
            } else {
                p[rank_val - 2]++; // 3~K 映射为 1~11
            }
        }

        dfs(0);
        cout << ans << "\n";
    }

    return 0;
}
