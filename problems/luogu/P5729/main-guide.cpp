/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-14 14:56
 * update_at: 2026-08-14 14:56
 */
#include <iostream>

int main() {
    const int max_size = 25;
    bool removed[max_size][max_size][max_size] = {};

    int width, depth, height;
    std::cin >> width >> depth >> height;

    int q;
    std::cin >> q;
    for (int k = 0; k < q; k += 1) {
        int x1, y1, z1, x2, y2, z2;
        std::cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
        // 输入坐标从 1 开始，数组下标从 0 开始，所以要整体减 1 再标记
        for (int x = x1 - 1; x <= x2 - 1; x += 1) {
            for (int y = y1 - 1; y <= y2 - 1; y += 1) {
                for (int z = z1 - 1; z <= z2 - 1; z += 1) {
                    removed[x][y][z] = true;
                }
            }
        }
    }

    int remaining = 0;
    // 遍历整个立方体，统计没有被切掉的小方块
    for (int x = 0; x < width; x += 1) {
        for (int y = 0; y < depth; y += 1) {
            for (int z = 0; z < height; z += 1) {
                if (!removed[x][y][z]) {
                    remaining += 1;
                }
            }
        }
    }

    std::cout << remaining;
    return 0;
}
