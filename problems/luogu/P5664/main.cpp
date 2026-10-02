/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-06-20 07:35
 * update_at: 2026-10-01 20:09
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 105;
const int MAXM = 2005;
const int MAXD = MAXN * 2 + 5;
const ll MOD = 998244353LL;

int n, m;
int a[MAXN][MAXM]; // a[i][j]：第 i 种做法用食材 j 的方案数，值域 < MOD，用 int
ll row_sum[MAXN];  // 第 i 行所有食材方案数之和（模 MOD）
ll dp[MAXD];       // dp[d]：当前差值为 d 的方案数，d 用偏移量 offset = n+1 映射到非负下标
ll ndp[MAXD];      // 下一行滚动数组

// 模意义下加法：x = (x + y) % MOD
void add_mod(ll &x, ll y) {
    x += y;
    if (x >= MOD) {
        x -= MOD;
    }
}

// 统计"食材 food 成为严格多数"的坏方案数。
// diff = 选 food 的次数 - 选其它食材的次数，
// 最终 diff > 0 表示 food 严格超过一半。
ll count_bad_for_food(int food) {
    int offset = n + 1;
    int left = offset;
    int right = offset;

    memset(dp, 0, sizeof(dp));
    dp[offset] = 1;

    for (int i = 1; i <= n; i++) {
        memset(ndp, 0, sizeof(ndp));

        ll same = a[i][food];           // 选食材 food 的方案数
        ll other = row_sum[i] - same;   // 选非 food 食材的方案数
        if (other < 0) {
            other += MOD;
        }

        for (int d = left; d <= right; d++) {
            ll cur = dp[d];
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

    ll ans = 0;
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

    // 不考虑"某种食材不能超过一半"时：
    // 每种做法要么不选，要么任选一种食材做一道菜。
    ll total = 1;
    for (int i = 1; i <= n; i++) {
        total = total * (row_sum[i] + 1) % MOD;
    }
    total = (total - 1 + MOD) % MOD; // 去掉空方案

    // 枚举哪一种食材成为"严格多数"，把所有坏方案扣掉。
    ll bad = 0;
    for (int food = 1; food <= m; food++) {
        add_mod(bad, count_bad_for_food(food));
    }

    ll ans = (total - bad) % MOD;
    if (ans < 0) {
        ans += MOD;
    }

    cout << ans << '\n';

    return 0;
}
