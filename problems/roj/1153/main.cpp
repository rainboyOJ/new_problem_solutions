/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 03:44
 * update_at: 2026-10-05 03:44
 */

#include <cstdio>
using namespace std;

typedef long long ll;

// 判断 n 是否为素数
bool is_prime(ll n) {
    if (n < 2) return false;
    for (ll i = 2; i * i <= n; ++i) {
        if (n % i == 0) return false;
    }
    return true;
}

int main() {
    // 枚举所有两位数，若自身与十位个位对换后均为素数则输出
    for (ll x = 10; x <= 99; ++x) {
        ll rev = (x % 10) * 10 + (x / 10);
        if (is_prime(x) && is_prime(rev)) {
            printf("%lld\n", x);
        }
    }
    return 0;
}
