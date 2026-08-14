/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-14 15:08
 * update_at: 2026-08-14 15:08
 */
#include <iostream>

const int max_size = 1024; // 2^10，n <= 10 时的最大边长

int grid[max_size][max_size]; // 0 表示被赦免，1 表示不被赦免

// 处理左上角为 (x, y)、边长为 size 的方阵
void solve(int x, int y, int size) {
    if (size == 1) {
        return; // 无法再分的单个格子，不用处理
    }
    int half = size / 2;

    // 左上角 half×half 区域整体赦免（填 0）
    for (int i = x; i < x + half; i += 1) {
        for (int j = y; j < y + half; j += 1) {
            grid[i][j] = 0;
        }
    }

    // 其余三个子方阵用同样的规则继续分治
    solve(x, y + half, half);        // 右上
    solve(x + half, y, half);        // 左下
    solve(x + half, y + half, half); // 右下
}

int main() {
    int n;
    std::cin >> n;
    int size = 1 << n; // 2^n 用左移 1 计算

    // 初始全部为 1（不被赦免）
    for (int i = 0; i < size; i += 1) {
        for (int j = 0; j < size; j += 1) {
            grid[i][j] = 1;
        }
    }

    solve(0, 0, size); // 从整个方阵开始分治

    for (int i = 0; i < size; i += 1) {
        for (int j = 0; j < size; j += 1) {
            std::cout << grid[i][j] << ' ';
        }
        std::cout << '\n';
    }
    return 0;
}
