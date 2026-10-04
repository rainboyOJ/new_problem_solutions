/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 04:10
 * update_at: 2026-10-05 04:10
 */
// main.cpp：逐位取模判断 30 位十进制大整数能被 2~9 中哪些数整除。
#include <iostream>
#include <string>

typedef long long ll;

std::string c; // c 的十进制表示，位数最多 30 位，只能按字符串读入

// 返回大整数 c 对 k 的余数：从高位到低位递推 r = (r * 10 + 当前位数字) % k
ll mod_big(ll k) {
    ll r = 0;
    ll len = c.size();
    for (ll i = 0; i < len; i++) {
        r = (r * 10 + (c[i] - '0')) % k;
    }
    return r;
}

int main() {
    std::cin >> c;
    bool found = false; // 是否已经找到至少一个因子，用来控制输出空格
    for (ll k = 2; k <= 9; k++) {
        if (mod_big(k) == 0) {
            if (found) {
                std::cout << ' ';
            }
            std::cout << k;
            found = true;
        }
    }
    if (!found) {
        std::cout << "none";
    }
    std::cout << std::endl;
    return 0;
}
