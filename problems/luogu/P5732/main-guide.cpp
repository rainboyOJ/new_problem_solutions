/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-14 14:56
 * update_at: 2026-08-14 14:56
 */
#include <iostream>

int main() {
    const int max_n = 25;
    int triangle[max_n][max_n] = {};

    int n;
    std::cin >> n;
    // 每行两端都是 1，中间元素等于上一行相邻两个数之和
    for (int row = 0; row < n; row += 1) {
        triangle[row][0] = 1;
        triangle[row][row] = 1;
        for (int col = 1; col < row; col += 1) {
            triangle[row][col] = triangle[row - 1][col - 1] + triangle[row - 1][col];
        }
    }

    for (int row = 0; row < n; row += 1) {
        for (int col = 0; col <= row; col += 1) {
            std::cout << triangle[row][col] << ' ';
        }
        std::cout << '\n';
    }
    return 0;
}
