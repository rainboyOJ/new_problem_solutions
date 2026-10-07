/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-07 15:27
 * update_at: 2026-10-07 15:27
 */
// main.cpp：新版方格取数。
// 状压 DP：dp[S][p] = 已取走的格子集合为 S、当前停在格 p 时的最大得分。
// 转移有两类：走到相邻未取格；当前在边缘格时"离开方格"，从任一未取边缘格重新进入。
// 每步取走第 k 个数得分 k * value[q]，所以刷表时用 k = popcount(S) + 1 直接乘。

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXCELL = 16;         // 格子数上限：m*n <= 16
const int MAXMASK = 1 << MAXCELL; // 集合掩码上限：2^16

int m, n;                 // m 行 n 列（题面顺序）
int total;                // 格子总数 m*n，把方格按行展平后第 i 格是第 i/n 行第 i%n 列
ll value[MAXCELL];        // value[i]：第 i 格里写的数
bool onEdge[MAXCELL];     // onEdge[i]：第 i 格是否位于方格边缘（只有边缘格能当起点或重新入口）
int nbr[MAXCELL][4];      // nbr[i][d]：第 i 格四个方向上的邻居编号，-1 表示越出方格
ll dp[MAXMASK][MAXCELL];  // dp[S][p]：已取集合 S、当前停在格 p 的最大得分；-1 表示该状态不可达

// 预处理每个格子的上下左右邻居编号，越界的记为 -1
void build_neighbors() {
    const int dr[4] = {-1, 1, 0, 0};
    const int dc[4] = {0, 0, -1, 1};
    for (int i = 0; i < total; i++) {
        int r = i / n, c = i % n;
        for (int d = 0; d < 4; d++) {
            int nr = r + dr[d], nc = c + dc[d];
            bool inside = (nr >= 0 && nr < m && nc >= 0 && nc < n);
            nbr[i][d] = inside ? nr * n + nc : -1;
        }
    }
}

// 用候选得分 val 去松弛 dp[S][p]：状态可能由多条取数顺序到达，取最大值
void relax(int S, int p, ll val) {
    if (val > dp[S][p]) dp[S][p] = val;
}

// 状压 DP 主体：返回最大总得分（一个数都不取时得 0 分，游戏允许中途结束）
ll solve_dp() {
    memset(dp, -1, sizeof(dp)); // 得分为非负，用 -1 标记不可达
    for (int p = 0; p < total; p++) {
        if (onEdge[p]) dp[1 << p][p] = value[p]; // 第 1 次取数必须从边缘格入手，得 1 * value[p]
    }

    ll ans = 0; // 游戏可以一开始就结束，也可以走到无路可走时结束
    for (int S = 1; S < (1 << total); S++) {
        for (int p = 0; p < total; p++) {
            ll cur = dp[S][p];
            if (cur < 0) continue;               // 该状态不可达
            int k = __builtin_popcount(S) + 1;   // 已取 popcount(S) 个，下一个取走的是第 k 个
            for (int d = 0; d < 4; d++) {        // (1) 走到相邻的未取格
                int q = nbr[p][d];
                if (q < 0 || (S >> q & 1)) continue;
                relax(S | 1 << q, q, cur + k * value[q]);
            }
            if (onEdge[p]) {                     // (2) 停在边缘格：可以离开方格再重新进入
                for (int q = 0; q < total; q++) {
                    if (!onEdge[q] || (S >> q & 1)) continue;
                    relax(S | 1 << q, q, cur + k * value[q]);
                }
            }
            if (cur > ans) ans = cur;            // 当前状态就是一个合法的结束时刻
        }
    }
    return ans;
}

int main() {
    if (scanf("%d %d", &m, &n) != 2) return 0;
    total = m * n;
    for (int i = 0; i < total; i++) scanf("%lld", &value[i]);
    for (int i = 0; i < total; i++) {
        int r = i / n, c = i % n;
        onEdge[i] = (r == 0 || r == m - 1 || c == 0 || c == n - 1);
    }

    build_neighbors();
    printf("%lld\n", solve_dp());
    return 0;
}
