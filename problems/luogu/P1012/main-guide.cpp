/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-14 14:55
 * update_at: 2026-08-14 14:55
 */
#include <iostream>
#include <string>
#include <algorithm>

const int max_n = 25;  // n <= 20

// 比较规则：x 排在 y 前面能拼出更大的数时返回 true。
// 只看拼接后的 x+y 和 y+x，谁大谁在前
bool better(const std::string& x, const std::string& y) {
    return x + y > y + x;
}

int main() {
    int n;
    std::cin >> n;
    std::string a[max_n];  // 数字按字符串保存，避免拼接时溢出
    for (int i = 0; i < n; i += 1) {
        std::cin >> a[i];
    }

    std::sort(a, a + n, better);  // 按"谁拼在前面更大"排序

    for (int i = 0; i < n; i += 1) {
        std::cout << a[i];  // 依次拼出最大的整数
    }
    std::cout << '\n';
    return 0;
}
