/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-14 15:08
 * update_at: 2026-08-14 15:08
 */
#include <iostream>

int main() {
    int integer_part = 0; // 小数点前的整数部分，如 123
    char dot = '\0';      // 读掉小数点本身
    int decimal_part = 0; // 小数点后的部分，如 4
    std::cin >> integer_part >> dot >> decimal_part;

    // 反转：先输出小数部分，再按 个位、十位、百位 依次取出整数部分的每一位
    std::cout << decimal_part << '.' << integer_part % 10
              << (integer_part / 10) % 10 << integer_part / 100 << '\n';
    return 0;
}
