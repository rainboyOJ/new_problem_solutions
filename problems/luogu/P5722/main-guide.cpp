/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-14 14:54
 * update_at: 2026-08-14 14:54
 */
#include <iostream>

// 返回 1 到 n 的和：把累加步骤独立成函数，main 只负责读入和输出
int sum_to(int n) {
    int sum = 0;
    for (int i = 1; i <= n; i += 1) {
        sum += i;
    }
    return sum;
}

int main() {
    int n;
    std::cin >> n;
    std::cout << sum_to(n) << '\n';
    return 0;
}
