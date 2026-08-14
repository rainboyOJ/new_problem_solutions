/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-14 14:54
 * update_at: 2026-08-14 14:54
 */
#include <algorithm>
#include <iostream>

int main() {
    int a, b, c; // 三个待排序的整数
    std::cin >> a >> b >> c;
    // 两两比较交换，使 a <= b <= c；每次交换后都要重新确认位置
    if (a > b) {
        std::swap(a, b);
    }
    if (b > c) {
        std::swap(b, c);
    }
    if (a > b) {
        std::swap(a, b);
    }
    std::cout << a << ' ' << b << ' ' << c << '\n';
    return 0;
}
