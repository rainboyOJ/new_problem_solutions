/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-14 14:54
 * update_at: 2026-08-14 14:54
 */
/* P1789 Mc生存：模拟火把与萤石的照亮范围，统计未被照亮的格子。 */

#include <iostream>
#include <cmath>

const int max_n = 105;  // n 最大为 100

bool lit[max_n][max_n];  // lit[row][col] = true 表示 (row, col) 被照亮
int n, torch_count, glowstone_count;

int main() {
    std::cin >> n >> torch_count >> glowstone_count;

    // 火把：照亮曼哈顿距离不超过 2 的格子。
    for (int k = 0; k < torch_count; k += 1) {
        int x, y;
        std::cin >> x >> y;
        x -= 1;  // 输入是 1 起始坐标，转成 0 起始下标
        y -= 1;
        for (int dx = -2; dx <= 2; dx += 1) {
            for (int dy = -2; dy <= 2; dy += 1) {
                if (std::abs(dx) + std::abs(dy) > 2) {
                    continue;  // 超出火把范围的角落格子
                }
                int nx = x + dx;
                int ny = y + dy;
                if (nx < 0 || nx >= n || ny < 0 || ny >= n) {
                    continue;  // 越界
                }
                lit[nx][ny] = true;
            }
        }
    }

    // 萤石：照亮以自己为中心的 5x5 正方形。
    for (int k = 0; k < glowstone_count; k += 1) {
        int x, y;
        std::cin >> x >> y;
        x -= 1;
        y -= 1;
        for (int dx = -2; dx <= 2; dx += 1) {
            for (int dy = -2; dy <= 2; dy += 1) {
                int nx = x + dx;
                int ny = y + dy;
                if (nx < 0 || nx >= n || ny < 0 || ny >= n) {
                    continue;  // 越界
                }
                lit[nx][ny] = true;
            }
        }
    }

    int dark_count = 0;  // 没被照亮、会生成怪物的格子数
    for (int row = 0; row < n; row += 1) {
        for (int col = 0; col < n; col += 1) {
            if (!lit[row][col]) {
                dark_count += 1;
            }
        }
    }
    std::cout << dark_count << '\n';
    return 0;
}
