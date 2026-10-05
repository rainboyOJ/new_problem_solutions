/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 23:47
 * update_at: 2026-10-05 23:47
 */

#include <iostream>
#include <numeric>
using namespace std;

typedef long long ll;

// 扩展欧几里得：求 a*x + b*y = gcd(a,b)，返回 gcd(a,b)。
ll exgcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    ll x1, y1;
    ll g = exgcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - a / b * y1;
    return g;
}

// 求 a 在模 m (>1) 下的逆元，调用前保证 gcd(a, m) == 1。
ll mod_inverse(ll a, ll m) {
    ll x, y;
    exgcd(a, m, x, y);
    return (x % m + m) % m;
}

// 把 x ≡ a2 (mod m2) 合并进当前同余式 x ≡ r1 (mod m1)。
// 有解时更新 r1、m1 为新同余式并返回 true；矛盾无解时返回 false。
bool merge_congruence(ll &r1, ll &m1, ll a2, ll m2) {
    ll g = gcd(m1, m2);
    ll diff = a2 - r1;
    if (diff % g != 0) {
        return false; // gcd 不整除差值，两条同余式矛盾
    }
    ll n = m2 / g; // 约去公因子后 m1/g 与 n 互质，可直接求逆元
    ll b = diff / g;
    b = (b % n + n) % n;
    ll k = 0;
    if (n > 1) {
        ll inv = mod_inverse((m1 / g) % n, n);
        k = b * inv % n; // 取模 m2/g 的最小非负 k
    }
    r1 = r1 + m1 * k; // 新余数已落在 [0, lcm) 内，天然最小
    m1 = m1 / g * m2; // 新模数变成 lcm(m1, m2)
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n;
    while (cin >> n) {
        ll r = 0; // 当前同余式 x ≡ r (mod m)，初值为恒成立式 x ≡ 0 (mod 1)
        ll m = 1;
        bool ok = true;
        for (ll i = 1; i <= n; i++) {
            ll mi, ai;
            cin >> mi >> ai;
            if (ok) {
                // 已判定无解仍要读完本组剩余输入，否则后续数据会错位。
                ok = merge_congruence(r, m, ai, mi);
            }
        }
        if (ok) {
            cout << r << "\n";
        } else {
            cout << -1 << "\n";
        }
    }

    return 0;
}
