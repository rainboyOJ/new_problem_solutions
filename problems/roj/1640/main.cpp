/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 00:12
 * update_at: 2026-10-06 00:12
 */
#include <iostream>
using namespace std;
typedef long long ll;

// 扩展欧几里得：求 g = gcd(a, b)，并给出 x, y 使 a*x + b*y = g
ll ext_gcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    ll x1, y1;
    ll g = ext_gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}

int main() {
    ll a, b, c, k;
    while (cin >> a >> b >> c >> k) {
        if (a == 0 && b == 0 && c == 0 && k == 0) {
            break;
        }
        ll mod = 1LL << k; // k 位系统的模数 2^k
        ll x, y;
        ll g = ext_gcd(c, mod, x, y); // g = gcd(C, 2^k)
        ll diff = b - a;              // 同余方程右端 Ct ≡ B - A (mod 2^k)
        if (diff % g != 0) {
            cout << "FOREVER" << "\n"; // gcd 不整除差值，永远到不了 B
            continue;
        }
        ll period = mod / g; // 解在模 period 意义下唯一
        // 把 x、diff/g 都化到 [0, period)，再用 __int128 相乘防止溢出
        x = ((x % period) + period) % period;
        ll factor = ((diff / g) % period + period) % period;
        __int128 prod = (__int128)x * factor;
        ll ans = prod % period; // 最小非负解
        cout << ans << "\n";
    }
    return 0;
}
