/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-14 14:54
 * update_at: 2026-08-14 14:54
 */
#include <iostream>

int main() {
    int n; // 整数的个数
    std::cin >> n;
    const int max_n = 105;
    int a[max_n]; // 存储读入的 n 个整数
    for (int i = 0; i < n; i += 1) {
        std::cin >> a[i];
    }
    // 最小值先取第一个数，再从第二个开始逐个比较更新
    int min_val = a[0];
    for (int i = 1; i < n; i += 1) {
        if (a[i] < min_val) {
            min_val = a[i];
        }
    }
    std::cout << min_val << '\n';
    return 0;
}
