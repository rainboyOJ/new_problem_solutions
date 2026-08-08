#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;
const int MAXS = 1 << 10;

int n, m;
int row_mask[MAXN];          // row_mask[i] 的 1 表示这一列是山地，不能放炮兵
int states[MAXS], state_cnt; // 所有单行合法状态
int bit_cnt[MAXS];           // bit_cnt[s] 表示状态 s 里放了多少个炮兵
int dp[2][MAXS][MAXS];
// dp[cur][s1][s2]：
// 已经处理到当前这一行时，当前行状态是 s1，上一行状态是 s2 的最大炮兵数。

bool ok_self(int s) {
    // 同一行里，距离 1 或 2 的两个炮兵都会互相攻击。
    if (s & (s << 1)) {
        return false;
    }
    if (s & (s << 2)) {
        return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        string s;
        cin >> s;
        int mask = 0;
        for (int j = 0; j < m; j++) {
            if (s[j] == 'H') {
                mask |= 1 << j;
            }
        }
        row_mask[i] = mask;
    }

    int full = 1 << m;
    state_cnt = 0;
    for (int s = 0; s < full; s++) {
        if (ok_self(s)) {
            states[state_cnt++] = s;
            bit_cnt[s] = __builtin_popcount((unsigned int) s);
        }
    }

    memset(dp, -1, sizeof(dp));
    dp[0][0][0] = 0;

    for (int row = 1; row <= n; row++) {
        int now = row & 1;
        int pre = now ^ 1;
        memset(dp[now], -1, sizeof(dp[now]));

        for (int i = 0; i < state_cnt; i++) {
            int cur = states[i];
            // 当前行不能把炮兵放在山地上。
            if (cur & row_mask[row]) {
                continue;
            }
            for (int j = 0; j < state_cnt; j++) {
                int pre1 = states[j];
                // 与上一行同列时会互相攻击。
                if (cur & pre1) {
                    continue;
                }
                for (int k = 0; k < state_cnt; k++) {
                    int pre2 = states[k];
                    // 与上上行同列时也会互相攻击。
                    if (cur & pre2) {
                        continue;
                    }
                    if (dp[pre][pre1][pre2] == -1) {
                        continue;
                    }
                    // 行号整体向下推进一格：
                    // 原来的上一行变成上上行，当前行变成新的上一行。
                    dp[now][cur][pre1] = max(dp[now][cur][pre1],
                                             dp[pre][pre1][pre2] + bit_cnt[cur]);
                }
            }
        }
    }

    int last = n & 1;
    int ans = 0;
    for (int i = 0; i < state_cnt; i++) {
        for (int j = 0; j < state_cnt; j++) {
            ans = max(ans, dp[last][states[i]][states[j]]);
        }
    }

    cout << ans << '\n';
    return 0;
}
