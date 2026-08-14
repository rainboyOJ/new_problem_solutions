/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-14 14:54
 * update_at: 2026-08-14 14:54
 */
#include <iostream>

int main() {
    int n; // 题目数量
    std::cin >> n;
    // 本地方案：每题 5 分钟
    int local = 5 * n;
    // 洛谷方案：每题 3 分钟，另需一次性花 11 分钟
    int luogu = 3 * n + 11;
    // 本地总耗时更短才输出 Local，相等或更长都输出 Luogu
    if (local < luogu) {
        std::cout << "Local" << '\n';
    } else {
        std::cout << "Luogu" << '\n';
    }
    return 0;
}
