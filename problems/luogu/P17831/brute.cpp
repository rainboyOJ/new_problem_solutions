/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-31 21:08
 * update_at: 2026-10-31 21:08
 */
// brute.cpp：枚举非空子集，只用于 n <= 16 的小数据与对拍。
#include <iostream>
#include <climits>
#include <algorithm>

using namespace std;

typedef long long ll;

const int MAXN = 25;
ll a[MAXN]; // 保留原顺序，直接枚举选哪些数

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n, m;
    if (!(cin >> n >> m)) return 0;
    for (ll i = 0; i < n; i++) {
        cin >> a[i];
    }

    ll ans = 1;
    // mask 的第 i 位为 1，表示选中 a[i]。
    for (ll mask = 1; mask < (1LL << n); mask++) {
        ll target = LLONG_MIN; // 输入可能全是负数，不能从 0 开始取最大值
        ll cnt = 0;
        for (ll i = 0; i < n; i++) {
            if ((mask >> i) & 1) {
                cnt++;
                target = max(target, a[i]);
            }
        }
        ll cost = 0;
        for (ll i = 0; i < n; i++) {
            if ((mask >> i) & 1) {
                cost += target - a[i];
            }
        }
        if (cost <= m) ans = max(ans, cnt);
    }

    cout << ans << "\n";
    return 0;
}
