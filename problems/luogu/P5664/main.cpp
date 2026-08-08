#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

const int MAXN = 105;
const int MAXM = 2005;
const int MAXD = MAXN * 2 + 5;
const i64 MOD = 998244353LL;

int n, m;
int a[MAXN][MAXM];
int row_sum[MAXN];
i64 dp[MAXD], ndp[MAXD];

void add_mod(i64 &x, i64 y) {
    x += y;
    if (x >= MOD) {
        x -= MOD;
    }
}

i64 count_bad_for_food(int food) {
    int offset = n + 1;
    int left = offset;
    int right = offset;

    memset(dp, 0, sizeof(dp));
    dp[offset] = 1;

    for (int i = 1; i <= n; i++) {
        memset(ndp, 0, sizeof(ndp));

        int same = a[i][food];
        int other = row_sum[i] - same;
        if (other < 0) {
            other += MOD;
        }

        for (int d = left; d <= right; d++) {
            i64 cur = dp[d];
            if (cur == 0) {
                continue;
            }

            // 第 i 种做法不选。
            add_mod(ndp[d], cur);

            // 选一个食材是 food 的菜，差值 +1。
            if (same != 0) {
                add_mod(ndp[d + 1], cur * same % MOD);
            }

            // 选一个食材不是 food 的菜，差值 -1。
            if (other != 0) {
                add_mod(ndp[d - 1], cur * other % MOD);
            }
        }

        left--;
        right++;
        memcpy(dp, ndp, sizeof(dp));
    }

    i64 ans = 0;
    for (int d = offset + 1; d <= right; d++) {
        add_mod(ans, dp[d]);
    }

    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> a[i][j];
            row_sum[i] += a[i][j];
            if (row_sum[i] >= MOD) {
                row_sum[i] -= MOD;
            }
        }
    }

    // 不考虑“某种食材不能超过一半”时：
    // 每种做法要么不选，要么任选一种食材做一道菜。
    i64 total = 1;
    for (int i = 1; i <= n; i++) {
        total = total * (row_sum[i] + 1LL) % MOD;
    }
    total = (total - 1 + MOD) % MOD; // 去掉空方案

    // 枚举哪一种食材成为“严格多数”，把所有坏方案扣掉。
    i64 bad = 0;
    for (int food = 1; food <= m; food++) {
        add_mod(bad, count_bad_for_food(food));
    }

    i64 ans = (total - bad) % MOD;
    if (ans < 0) {
        ans += MOD;
    }

    cout << ans << '\n';

    return 0;
}
