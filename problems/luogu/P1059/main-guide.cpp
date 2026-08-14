/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-14 15:18
 * update_at: 2026-08-14 15:18
 */
/* P1059 明明的随机数：布尔数组当桶用，相同的随机数只保留一个，再从小到大输出。 */

#include <iostream>

int main() {
    const int max_value = 1000;
    bool seen[max_value + 1];  // seen[x] = true 表示随机数 x 已经出现过
    for (int i = 1; i <= max_value; i += 1) {
        seen[i] = false;
    }

    int n;
    std::cin >> n;
    for (int i = 0; i < n; i += 1) {
        int x;
        std::cin >> x;
        seen[x] = true;  // 重复出现的数字只算一个
    }

    // 第一行输出不同数字的个数
    int count = 0;
    for (int i = 1; i <= max_value; i += 1) {
        if (seen[i]) {
            count += 1;
        }
    }
    std::cout << count << '\n';

    // 第二行按从小到大输出这些不同的数字
    bool first = true;
    for (int i = 1; i <= max_value; i += 1) {
        if (seen[i]) {
            if (!first) {
                std::cout << ' ';
            }
            std::cout << i;
            first = false;
        }
    }
    std::cout << '\n';

    return 0;
}
