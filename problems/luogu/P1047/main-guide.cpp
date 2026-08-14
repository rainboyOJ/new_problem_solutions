/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-14 15:18
 * update_at: 2026-08-14 15:18
 */
/* P1047 校门外的树：布尔数组记录每个位置是否被移走，最后统计留在原处的树。 */

#include <iostream>

int main() {
    const int max_length = 10000;  // 路的长度最大为 10000

    int road_length, zone_count;
    std::cin >> road_length >> zone_count;

    bool removed[max_length + 1];  // removed[i] = true 表示位置 i 的树被移走
    for (int i = 0; i <= road_length; i += 1) {
        removed[i] = false;
    }

    // 施工区间 [left, right] 内的树逐点标记为移走，区间包含端点
    for (int k = 0; k < zone_count; k += 1) {
        int left, right;
        std::cin >> left >> right;
        for (int i = left; i <= right; i += 1) {
            removed[i] = true;
        }
    }

    // 统计没有被移走的树
    int answer = 0;
    for (int i = 0; i <= road_length; i += 1) {
        if (!removed[i]) {
            answer += 1;
        }
    }

    std::cout << answer << '\n';
    return 0;
}
