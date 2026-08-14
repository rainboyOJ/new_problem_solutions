/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-14 14:54
 * update_at: 2026-08-14 14:54
 */
/* P1980 计数问题：枚举 1..n 的每个数，逐位统计数字 x 出现次数。 */

#include <iostream>

int main() {
    int n, x;
    std::cin >> n >> x;

    int total = 0;  // x 出现的总次数
    for (int number = 1; number <= n; number += 1) {
        int temp = number;  // 拷贝一份，逐位拆数时不会破坏循环变量
        while (temp > 0) {
            int digit = temp % 10;  // 取出当前最低位
            if (digit == x) {
                total += 1;
            }
            temp /= 10;  // 去掉最低位，继续看下一位
        }
    }
    std::cout << total << '\n';
    return 0;
}
