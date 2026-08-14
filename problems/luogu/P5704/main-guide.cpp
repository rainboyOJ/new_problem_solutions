/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-14 15:08
 * update_at: 2026-08-14 15:08
 */
#include <iostream>

int main() {
    char lowercase;
    std::cin >> lowercase;
    // 小写字母与大写字母在 ASCII 码表中相差固定值，用 'a' - 'A' 表示更清楚
    std::cout << static_cast<char>(lowercase - 'a' + 'A') << '\n';
    return 0;
}
