/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 00:59
 * update_at: 2026-10-05 00:59
 */
// main.cpp：试除法求较大的质因子。
// n = p*q 且 p<q 为两个不同质数，从小到大第一个整除 n 的 d 就是 p，答案 n/p。
#include <iostream>

typedef long long ll;

int main() {
    ll n;
    std::cin >> n;

    // p < sqrt(n) < q，枚举到 sqrt(n) 即可；找到的第一个因子必为较小质数 p。
    for (ll d = 2; d * d <= n; d++) {
        if (n % d == 0) {
            std::cout << n / d << std::endl;
            return 0;
        }
    }

    // 理论上 n 至少含两个不同质因子，不会走到这里。
    std::cout << 1 << std::endl;
    return 0;
}
