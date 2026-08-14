/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-14 14:53
 * update_at: 2026-08-14 14:53
 */
#include <iostream>

const int max_n = 105;

int main() {
    int n;
    std::cin >> n;

    int cute[max_n];
    for (int i = 0; i < n; i += 1) {
        std::cin >> cute[i];
    }

    // 对每条鱼，只看它左边 0..i-1 的鱼；"不如自己可爱"要求严格小于
    for (int i = 0; i < n; i += 1) {
        int count = 0;
        for (int j = 0; j < i; j += 1) {
            if (cute[j] < cute[i]) {
                count += 1;
            }
        }
        std::cout << count << ' ';
    }
    std::cout << '\n';

    return 0;
}
