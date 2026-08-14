/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-14 14:54
 * update_at: 2026-08-14 14:54
 */
#include <iomanip>
#include <iostream>

// 输出三角形第 row 行（row 从 0 开始）：这一行有 (n - row) 个数字，
// number 是当前要输出的数字，每输出一个就向后推进
void print_row(int n, int row, int& number) {
    for (int i = 0; i < n - row; i += 1) {
        std::cout << std::setw(2) << std::setfill('0') << number;
        number += 1;
    }
    std::cout << '\n';
}

int main() {
    int n; // 直角边长度，也是第一行的数字个数
    std::cin >> n;
    int number = 1; // 当前要输出的数字，从 1 开始连续递增
    for (int row = 0; row < n; row += 1) {
        print_row(n, row, number);
    }
    return 0;
}
