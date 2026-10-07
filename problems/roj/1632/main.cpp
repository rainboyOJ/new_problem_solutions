/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 01:24
 * update_at: 2026-10-06 01:24
 */
#include <iostream>

typedef long long ll;

// 扩展欧几里得：求出 a*x + b*y = gcd(a, b) 的一组特解 x, y
ll exgcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    ll g = exgcd(b, a % b, x, y);
    ll nx = y;
    ll ny = x - (a / b) * y;
    x = nx;
    y = ny;
    return g;
}

int main() {
    ll a, b;
    std::cin >> a >> b;

    ll x, y;
    exgcd(a, b, x, y);

    // 通解为 x + k*b，把特解调整到 [1, b] 内的最小正整数
    ll ans = (x % b + b) % b;
    if (ans == 0) {
        ans = b;
    }
    std::cout << ans << std::endl;
    return 0;
}
