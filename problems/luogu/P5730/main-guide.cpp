/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-14 14:56
 * update_at: 2026-08-14 14:56
 */
#include <iostream>
#include <string>

int main() {
    // 每个数字 0~9 的 5 行 3 列点阵，X 表示亮点，. 表示暗点
    const char digit_pattern[10][5][4] = {
        {"XXX", "X.X", "X.X", "X.X", "XXX"}, // 数字 0
        {"..X", "..X", "..X", "..X", "..X"}, // 数字 1
        {"XXX", "..X", "XXX", "X..", "XXX"}, // 数字 2
        {"XXX", "..X", "XXX", "..X", "XXX"}, // 数字 3
        {"X.X", "X.X", "XXX", "..X", "..X"}, // 数字 4
        {"XXX", "X..", "XXX", "..X", "XXX"}, // 数字 5
        {"XXX", "X..", "XXX", "X.X", "XXX"}, // 数字 6
        {"XXX", "..X", "..X", "..X", "..X"}, // 数字 7
        {"XXX", "X.X", "XXX", "X.X", "XXX"}, // 数字 8
        {"XXX", "X.X", "XXX", "..X", "XXX"}  // 数字 9
    };

    int n;
    std::cin >> n;
    std::string digits;
    std::cin >> digits;

    // 按行输出：每行依次取每个数字的同一行点阵，数字之间插一列点
    for (int row = 0; row < 5; row += 1) {
        for (int i = 0; i < n; i += 1) {
            int d = digits[i] - '0';
            std::cout << digit_pattern[d][row];
            if (i != n - 1) {
                std::cout << '.';
            }
        }
        std::cout << '\n';
    }
    return 0;
}
