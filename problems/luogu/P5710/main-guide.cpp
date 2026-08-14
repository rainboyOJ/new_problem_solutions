/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-14 14:54
 * update_at: 2026-08-14 14:54
 */
#include <iostream>

int main() {
    int x; // 待判断的整数
    std::cin >> x;
    // 两个布尔性质：a 表示偶数，b 表示大于 4 且不大于 12
    bool a = (x % 2 == 0);
    bool b = (x > 4 && x <= 12);
    // 小 A 两个都满足，Uim 至少一个，小 B 恰好一个，正妹两个都不满足
    std::cout << (a && b) << ' ' << (a || b) << ' ' << (a != b) << ' ' << !(a || b) << '\n';
    return 0;
}
