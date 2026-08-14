/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-14 14:57
 * update_at: 2026-08-14 14:57
 */
#include <iostream>

long long factorial(int n) {
    // 0! = 1 是递归的停止条件
    if (n == 0) {
        return 1;
    }
    // n! = n * (n-1)!，把求阶乘变成求更小的阶乘
    return n * factorial(n - 1);
}

int main() {
    int n;
    std::cin >> n;
    std::cout << factorial(n) << '\n';
    return 0;
}
