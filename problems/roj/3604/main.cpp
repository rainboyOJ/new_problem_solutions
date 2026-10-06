/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 15:06
 * update_at: 2026-10-06 15:06
 */

#include <bits/stdc++.h>

typedef long long ll;

// 统计 1..n 的十进制表示中数字 x 一共出现了多少次（数位统计）
ll count_digit(ll n, ll x) {
    ll total = 0;
    ll p = 1; // 当前考察的数位权重：1 是个位，10 是十位，以此类推
    while (p <= n) {
        // 把 n 在这一位切成三段：高位 / 当前位 / 低位
        ll high = n / (p * 10);
        ll cur = n / p % 10;
        ll low = n % p;

        // 当前位取 0..x-1：前缀只能取 0..high-1，后缀任取 0..p-1
        total += high * p;
        // 当前位与 x 的比较决定前缀恰好取 high 时的后缀范围
        if (cur > x)
            total += p;        // 后缀任取 0..p-1
        else if (cur == x)
            total += low + 1;  // 后缀只能取 0..low，数 n 自己也算在内

        if (x == 0)
            total -= p; // 前导零修正：前缀全 0 的“数”并不存在，每层恰好多算 p 个
        p *= 10;
    }
    return total;
}

int main() {
    ll n, x;
    std::cin >> n >> x;
    std::cout << count_digit(n, x) << std::endl;
    return 0;
}
