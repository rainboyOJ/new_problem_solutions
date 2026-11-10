/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-11 00:32
 * update_at: 2026-11-11 00:32
 */
#include <iostream>

using namespace std;

using ll = long long;

// 计算 (base^exp) % mod
ll quick_pow(ll base, ll exp, ll mod) {
    ll ans = 1 % mod;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) ans = (ans * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n, m, k, x;
    if (!(cin >> n >> m >> k >> x)) return 0;

    // 10^k 轮后，总位移等于 m * (10^k % n)
    ll p = quick_pow(10, k, n);
    ll ans = (x + m * p) % n;

    cout << ans << "\n";

    return 0;
}
