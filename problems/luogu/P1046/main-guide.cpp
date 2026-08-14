/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-14 15:18
 * update_at: 2026-08-14 15:18
 */
/* P1046 陶陶摘苹果：读入 10 个苹果高度，统计踩上板凳后能够到的苹果数。 */

#include <iostream>

int main() {
    const int apple_count = 10;
    int height[apple_count];  // 10 个苹果离地的高度

    for (int i = 0; i < apple_count; i += 1) {
        std::cin >> height[i];
    }

    int hand_reach;
    std::cin >> hand_reach;

    // 踩上 30 厘米的板凳后，能够到的最大高度
    int reachable = hand_reach + 30;

    // 高度不超过 reachable 的苹果都能摘到
    int answer = 0;
    for (int i = 0; i < apple_count; i += 1) {
        if (height[i] <= reachable) {
            answer += 1;
        }
    }

    std::cout << answer << '\n';
    return 0;
}
