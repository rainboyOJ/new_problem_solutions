/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-14 14:55
 * update_at: 2026-08-14 14:55
 */
#include <iostream>

// 输出 n 的题目规定表示，例如 1315 输出 2(2(2+2(0))+2)+...
void decompose(int n) {
    if (n == 1) {
        std::cout << "2(0)";  // 2^0 写成 2(0)
        return;
    }
    if (n == 2) {
        std::cout << "2";  // 2^1 直接写成 2
        return;
    }
    // n <= 20000 < 2^15，所以只需要检查第 0 到第 14 位
    bool first = true;  // 第一个输出的项前面不需要加号
    for (int bit = 14; bit >= 0; bit -= 1) {
        if (((1 << bit) & n) == 0) {
            continue;  // 这一位是 0，不输出任何项
        }
        if (!first) {
            std::cout << "+";  // 后面的项之前都要补一个加号
        }
        first = false;
        if (bit == 0) {
            std::cout << "2(0)";
        } else if (bit == 1) {
            std::cout << "2";
        } else {
            std::cout << "2(";
            decompose(bit);  // 指数也要按同样的规则递归分解
            std::cout << ")";
        }
    }
}

int main() {
    int n;
    std::cin >> n;
    decompose(n);
    return 0;
}
