/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-14 14:54
 * update_at: 2026-08-14 14:54
 */
#include <iostream>

int main() {
    int year;
    std::cin >> year;
    // 闰年规则：能被 4 整除但不能被 100 整除，或能被 400 整除
    bool is_leap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    std::cout << is_leap << '\n';
    return 0;
}
