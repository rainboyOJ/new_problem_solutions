/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-14 15:18
 * update_at: 2026-08-14 15:18
 */
/* P1217 回文质数：组合「回文判断」和「质数判断」两个函数，只枚举少量回文候选。 */

#include <iostream>

// 试除法判断 x 是否为质数
bool is_prime(int x) {
    if (x < 2) {
        return false;
    }
    if (x == 2) {
        return true;
    }
    if (x % 2 == 0) {
        return false;  // 除 2 以外的偶数都不是质数
    }
    for (int d = 3; 1LL * d * d <= x; d += 2) {
        if (x % d == 0) {
            return false;
        }
    }
    return true;
}

// 判断 x 正着读和倒着读是否相同
bool is_palindrome(int x) {
    int reversed = 0;
    int rest = x;
    while (rest > 0) {
        reversed = reversed * 10 + rest % 10;  // 把 rest 的最低位搬到 reversed 前面
        rest /= 10;
    }
    return reversed == x;
}

// 由种子 x 构造奇数位回文数：12 -> 121，305 -> 30503
int make_odd_palindrome(int x) {
    int result = x;
    x /= 10;  // 最低位作为回文的中心，不再参与镜像
    while (x > 0) {
        result = result * 10 + x % 10;
        x /= 10;
    }
    return result;
}

int main() {
    int a, b;
    std::cin >> a >> b;

    // 一位数回文
    for (int x = 1; x <= 9; x += 1) {
        if (a <= x && x <= b && is_prime(x)) {
            std::cout << x << '\n';
        }
    }

    // 唯一可能是质数的偶数位回文数是 11
    if (a <= 11 && 11 <= b && is_prime(11)) {
        std::cout << 11 << '\n';
    }

    // 由种子 10..9999 构造 3、5、7、9 位回文数，按升序出现
    for (int seed = 10; seed <= 9999; seed += 1) {
        int palindrome = make_odd_palindrome(seed);
        if (palindrome > b) {
            break;  // 种子越大构造结果越大，后面的都不在区间内
        }
        if (palindrome < a) {
            continue;
        }
        // 构造保证是回文，这里组合两个判断函数作为校验
        if (is_palindrome(palindrome) && is_prime(palindrome)) {
            std::cout << palindrome << '\n';
        }
    }

    return 0;
}
