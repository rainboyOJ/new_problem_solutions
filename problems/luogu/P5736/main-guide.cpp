/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-14 14:56
 * update_at: 2026-08-14 14:56
 */
#include <iostream>

// 判断 x 是否为质数：只能被 1 和它本身整除
bool is_prime(int x) {
    if (x < 2) {
        return false;
    }
    // 因子总是成对出现，所以只需试除到 sqrt(x)
    for (int divisor = 2; divisor * divisor <= x; divisor += 1) {
        if (x % divisor == 0) {
            return false;
        }
    }
    return true;
}

int main() {
    int n;
    std::cin >> n;
    for (int i = 0; i < n; i += 1) {
        int x;
        std::cin >> x;
        if (is_prime(x)) {
            std::cout << x << ' ';
        }
    }
    return 0;
}
