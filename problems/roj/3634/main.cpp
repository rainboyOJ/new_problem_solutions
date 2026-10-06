/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 15:31
 * update_at: 2026-10-06 15:31
 */

#include <iostream>
#include <algorithm>
using namespace std;

typedef long long ll;

ll n;
ll a[4], p[4]; // 三种包装：a[i] 每包数量，p[i] 每包价格

// 买第 i 种包装至少凑够 n 支的花费：向上取整份数 × 单价
ll cost(ll i) {
    ll k = (n + a[i] - 1) / a[i]; // 最少份数
    return k * p[i];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= 3; ++i) cin >> a[i] >> p[i];

    ll ans = cost(1);
    for (int i = 2; i <= 3; ++i)
        ans = min(ans, cost(i));

    cout << ans << "\n";
    return 0;
}
