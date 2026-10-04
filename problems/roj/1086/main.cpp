/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 00:33
 * update_at: 2026-10-05 00:33
 */
// main.cpp：按角谷猜想规则反复变换 n，输出每一步算式，最后输出 End。
#include <iostream>

typedef long long ll;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    ll n; // 当前数值，角谷过程会把它放大，用 ll 更安全
    std::cin >> n;

    // n 为 1 时不进循环，直接输出 End
    while (n != 1) {
        if (n % 2 == 1) { // 奇数：变成 3n+1
            ll nxt = n * 3 + 1;
            std::cout << n << "*3+1=" << nxt << "\n";
            n = nxt;
        } else { // 偶数：变成 n/2
            ll nxt = n / 2;
            std::cout << n << "/2=" << nxt << "\n";
            n = nxt;
        }
    }
    std::cout << "End" << "\n";
    return 0;
}
