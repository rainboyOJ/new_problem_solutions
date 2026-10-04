/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 00:27
 * update_at: 2026-10-05 00:27
 */
#include <iostream>
#include <numeric>
using namespace std;

typedef long long ll;

ll a, b, c;

// 求 x 的最小大于 1 的因子
ll min_factor(ll x) {
    for (ll i = 2; i * i <= x; ++i)
        if (x % i == 0) return i;
    return x; // x 本身是素数
}

int main() {
    cin >> a >> b >> c;
    ll g = gcd(a - b, b - c); // C++17 gcd 返回非负
    if (g == 0) {             // a == b == c 时任意 x > 1 都合法
        cout << 2 << endl;
        return 0;
    }
    cout << min_factor(g) << endl;
    return 0;
}
