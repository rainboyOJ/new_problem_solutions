#include <bits/stdc++.h>
using namespace std;

const int MOD = 100000000;
const int MAXN = 15;
const int MAXS = 1 << 12;

int n, m;
int allow_mask[MAXN];        // allow_mask[i] 的 1 表示这一格可以种草
int states[MAXS], state_cnt; // 所有单行内部合法状态
int dp[2][MAXS];

bool ok_self(int s) {
    // 同一行里不能出现相邻的两块草地。
    return (s & (s << 1)) == 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        int mask = 0;
        for (int j = 0; j < m; j++) {
            int x;
            cin >> x;
            if (x == 1) {
                mask |= 1 << j;
            }
        }
        allow_mask[i] = mask;
    }

    int full = 1 << m;
    for (int s = 0; s < full; s++) {
        if (ok_self(s)) {
            states[state_cnt++] = s;
        }
    }

    memset(dp, 0, sizeof(dp));
    dp[0][0] = 1;

    for (int row = 1; row <= n; row++) {
        int now = row & 1;
        int pre = now ^ 1;
        memset(dp[now], 0, sizeof(dp[now]));

        for (int i = 0; i < state_cnt; i++) {
            int cur = states[i];
            // 当前行选的位置必须全部是可种草的土地。
            if ((cur & allow_mask[row]) != cur) {
                continue;
            }

            for (int j = 0; j < state_cnt; j++) {
                int last = states[j];
                // 上下两行不能在同一列都种草。
                if (cur & last) {
                    continue;
                }
                dp[now][cur] += dp[pre][last];
                if (dp[now][cur] >= MOD) {
                    dp[now][cur] -= MOD;
                }
            }
        }
    }

    int last = n & 1;
    int ans = 0;
    for (int i = 0; i < state_cnt; i++) {
        ans += dp[last][states[i]];
        if (ans >= MOD) {
            ans -= MOD;
        }
    }

    cout << ans << '\n';
    return 0;
}
