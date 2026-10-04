/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-04 21:36
 * update_at: 2026-10-04 21:36
 */
// main.cpp：读入两个整数，输出它们的和。
#include <iostream>

typedef long long ll;

int main() {
    ll a, b; // 题面没有数据范围，用 ll 保证不溢出
    std::cin >> a >> b;
    std::cout << a + b << std::endl;
    return 0;
}
