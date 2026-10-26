/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-26 13:45
 * update_at: 2026-10-26 16:36
 */
// subtask_nv.cpp：按公差建桶的 DP，直接 dp[i][d] 记录公差 d，适用于 v <= 2e3 的 60% 档。
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MOD = 998244353;
const int MAXN = 1005;  // n <= 1000
const int MAXV = 2005;  // 本题档位的高度上限 v <= 2e3, 负数公差靠偏移量 v 平移

ll n;
ll h[MAXN];       // h[i]: 第 i 座塔的高度, 下标从 1 开始
ll v;              // v = 最高的塔
ll dp[MAXN][2 * MAXV];  // dp[i][d + v]: 以第 i 座塔结尾、公差为 d 且长度 >= 2 的等差子序列个数

void read_input() {
    cin >> n;
    for (ll i = 1; i <= n; i++) {
        cin >> h[i];
        v = max(v, h[i]);
    }
}

void solve() {
    ll ans = n; // 长度 1 的子序列一定等差
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j < i; j++) {
            ll d = h[i] - h[j];        // 公差可为负, 下标要加偏移 v
            // 前一项是 h[j] 的等差子序列接上 h[i], 再加上只取 j, i 两项这一种
            ll ways = dp[j][d + v] + 1;
            dp[i][d + v] = (dp[i][d + v] + ways) % MOD;
            ans = (ans + ways) % MOD;
        }
    }
    cout << ans % MOD << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    solve();
    return 0;
}
