/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-01 09:34
 * update_at: 2026-11-01 09:34
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN = 5005;
const ll MOD = 998244353;
ll n, budget;
ll a[MAXN]; // 原价，按降序排列
ll factorial[MAXN], inverse[MAXN], inverse_factorial[MAXN], power_two[MAXN];

// 线性逆元骨架取自 rbook 的 line-inv 模板，n<MOD。
void prepare() {
    factorial[0] = inverse_factorial[0] = power_two[0] = 1;
    inverse[1] = 1;
    for (ll i = 1; i < MAXN; i++) {
        if (i > 1) inverse[i] = (MOD - MOD / i) * inverse[MOD % i] % MOD;
        factorial[i] = factorial[i - 1] * i % MOD;
        inverse_factorial[i] = inverse_factorial[i - 1] * inverse[i] % MOD;
        power_two[i] = power_two[i - 1] * 2 % MOD;
    }
}

ll choose(ll total, ll selected) {
    if (selected < 0 || selected > total) return 0;
    return factorial[total] * inverse_factorial[selected] % MOD *
           inverse_factorial[total - selected] % MOD;
}

void solve() {
    cin >> n >> budget;
    for (ll i = 1; i <= n; i++) cin >> a[i];
    sort(a + 1, a + n + 1, greater<ll>());

    ll bad = 0;
    for (ll missed = 1; missed <= n; missed++) {
        // i 前改成二元的点，与 i、j 之间定一元的点，总共需选这么多。
        ll extra = budget - missed - 1;
        if (extra < 0) break;
        ll free_start = n + 1;
        ll first_blocker = max(missed + 1, budget - missed + 1);
        for (ll blocker = first_blocker; blocker <= n; blocker++) {
            if (a[missed] == a[blocker]) continue; // 等值交换不会提升价值
            if (a[missed] >= 2 * a[blocker]) break; // 等密度时二元高原价先考虑

            // 这里之后的糖即使定一元，补买后仍无法弥补这次价值损失。
            while (free_start > blocker + 1 &&
                   a[free_start - 1] + a[blocker] < a[missed]) {
                free_start--;
            }
            ll ways = choose(blocker - 2, extra) * power_two[n - free_start + 1] % MOD;
            bad = (bad + ways) % MOD;
        }
    }
    cout << (power_two[n] - bad + MOD) % MOD << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    prepare();
    ll control_id, tests;
    cin >> control_id >> tests;
    while (tests--) solve();
    return 0;
}
