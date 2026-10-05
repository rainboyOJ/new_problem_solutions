/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 11:23
 * update_at: 2026-10-05 11:23
 */
// main.cpp：按行状压 DP，统计网格上不相邻种草方案数。
#include <cstdio>

typedef long long ll;

const int MAXN = 13;
const ll MOD = 100000000; // 题面要求方案数对 10^8 取模

int m, n;
int fertile[MAXN];            // fertile[r]：第 r 行肥沃格掩码，第 c 位为 1 表示可种草
int valid_mask[1 << MAXN];    // 所有不含横向相邻 1 的掩码
int valid_cnt;

ll dp[1 << MAXN];   // dp[s]：处理到上一行、且上一行种植掩码恰为 s 的方案数
ll nxt[1 << MAXN];  // nxt[s]：处理到本行、且本行种植掩码恰为 s 的方案数

int main() {
    scanf("%d%d", &m, &n);
    for (int r = 0; r < m; r++) {
        int mask = 0;
        for (int c = 0; c < n; c++) {
            int x;
            scanf("%d", &x);
            if (x == 1) {
                mask |= 1 << c; // 第 c 位为 1 表示这一格肥沃
            }
        }
        fertile[r] = mask;
    }

    // 与行无关的公共候选：掩码内部没有两个相邻的 1
    valid_cnt = 0;
    for (int s = 0; s < (1 << n); s++) {
        if ((s & (s << 1)) == 0) {
            valid_mask[valid_cnt] = s;
            valid_cnt++;
        }
    }

    // 初始时把第 0 行上方视为空行，只有空掩码 1 种方案
    for (int s = 0; s < (1 << n); s++) {
        dp[s] = 0;
    }
    dp[0] = 1;

    for (int r = 0; r < m; r++) {
        for (int s = 0; s < (1 << n); s++) {
            nxt[s] = 0;
        }
        for (int i = 0; i < valid_cnt; i++) {
            int s = valid_mask[i];
            if (s & ~fertile[r]) {
                continue; // 该掩码踩到了贫瘠格
            }
            ll sum = 0;
            for (int j = 0; j < valid_cnt; j++) {
                int t = valid_mask[j];
                if (s & t) {
                    continue; // 与上一行同列同时种草，会产生纵向相邻
                }
                sum += dp[t];
            }
            nxt[s] = sum % MOD;
        }
        for (int s = 0; s < (1 << n); s++) {
            dp[s] = nxt[s]; // 滚动到下一行
        }
    }

    // 末行任意合法掩码都可以作为结尾，求和即总方案数（含全程不种）
    ll ans = 0;
    for (int s = 0; s < (1 << n); s++) {
        ans = (ans + dp[s]) % MOD;
    }
    printf("%lld\n", ans);
    return 0;
}
