/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-04 22:22
 * update_at: 2026-10-04 22:22
 */

#include <iostream>

typedef long long ll;

ll a, b, c; // 输入的三个整数，c 不为 0

int main() {
    std::cin >> a >> b >> c;
    // C++ 的整数除法本身就是向零取整，正好是题目要求的语义
    ll total = a + b;
    std::cout << total / c << std::endl;
    return 0;
}
