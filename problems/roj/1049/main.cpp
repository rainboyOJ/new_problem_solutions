/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-04 23:29
 * update_at: 2026-10-04 23:29
 */
// main.cpp：晶晶每周固定 1、3、5 有课，输入 1~7 表示周一到周日，判断能否赴约。
#include <iostream>

typedef long long ll;

int main() {
    ll d; // 邀请日期，1 表示周一，7 表示周日
    std::cin >> d;
    std::cout << ((d == 1 || d == 3 || d == 5) ? "NO" : "YES") << std::endl;
    return 0;
}