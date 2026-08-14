/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-14 14:53
 * update_at: 2026-08-14 14:53
 */
#include <iostream>

int main() {
    int yuan, jiao;
    std::cin >> yuan >> jiao;

    // 统一成最小单位"角"：1 元 = 10 角，一支笔是 1 元 9 角 = 19 角
    int total_jiao = yuan * 10 + jiao;

    // 整数除法表示"总角数里最多有几个完整的 19 角"
    std::cout << total_jiao / 19 << '\n';

    return 0;
}
