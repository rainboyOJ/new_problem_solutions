/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 11:17
 * update_at: 2026-10-05 11:17
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 11;
const int MAXK = 105;
const int MAXS = 1 << 10; // 单行状态掩码上限：n <= 10

int n, k;
int all_state[MAXS]; // 合法单行状态（行内无左右相邻国王）的掩码列表
int state_num;       // 合法状态个数
int kings[MAXS];     // kings[s]：状态 s 这一行的国王数（置位数）

// dp[cur][j][s]：处理到当前行、已放 j 个国王、当前行状态为 s 的方案数
// 用 0/1 两层滚动，cur 表示当前层
ll dp[2][MAXK][MAXS];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;

    // 预处理单行合法状态：国王攻击左右格，行内不能有相邻的 1
    for (int s = 0; s < (1 << n); s++) {
        if ((s & (s << 1)) == 0) {
            all_state[state_num] = s;
            // 统计该状态国王数
            int c = 0;
            for (int i = 0; i < n; i++) {
                if (s & (1 << i)) c++;
            }
            kings[s] = c;
            state_num++;
        }
    }

    int cur = 0;
    // 初始：还没放任何行，0 个国王，上一行（哨兵）状态为空
    dp[cur][0][0] = 1;

    for (int row = 1; row <= n; row++) {
        int nxt = cur ^ 1;
        // 先清空新一层
        for (int j = 0; j <= k; j++) {
            for (int a = 0; a < state_num; a++) {
                dp[nxt][j][all_state[a]] = 0;
            }
        }
        // 枚举上一行状态 a、当前行状态 b，相容则转移
        for (int a = 0; a < state_num; a++) {
            int sa = all_state[a];
            for (int b = 0; b < state_num; b++) {
                int sb = all_state[b];
                // 同列不冲突、左斜不冲突、右斜不冲突
                if (sa & sb) continue;
                if (sa & (sb << 1)) continue;
                if (sa & (sb >> 1)) continue;
                for (int j = 0; j + kings[sb] <= k; j++) {
                    dp[nxt][j + kings[sb]][sb] += dp[cur][j][sa];
                }
            }
        }
        cur = nxt;
    }

    // 答案：所有行处理完后恰好放了 k 个国王的所有方案
    ll ans = 0;
    for (int a = 0; a < state_num; a++) {
        ans += dp[cur][k][all_state[a]];
    }
    cout << ans << "\n";

    return 0;
}
