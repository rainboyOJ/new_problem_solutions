/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-04 22:12
 * update_at: 2026-10-05 23:11
 */
#include <iostream>
using namespace std;

typedef long long ll;

// 判断 x 是否为回文数：十进制表示左右对称
bool is_palindrome(ll x) {
    ll rev = 0, t = x;
    while (t > 0) {
        rev = rev * 10 + t % 10;
        t /= 10;
    }
    return rev == x;
}

// 判断 x 是否为素数：试除到 sqrt(x)
bool is_prime(ll x) {
    if (x < 2) return false;
    for (ll i = 2; i * i <= x; ++i)
        if (x % i == 0) return false;
    return true;
}

ll n;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    ll ans = 0;
    // 先判回文（快且筛掉多数），再判素数
    for (ll i = 11; i <= n; ++i)
        if (is_palindrome(i) && is_prime(i)) ++ans;
    cout << ans << '\n';
    return 0;
}
