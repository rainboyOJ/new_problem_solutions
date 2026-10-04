/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 05:57
 * update_at: 2026-10-05 05:57
 */
#include <bits/stdc++.h>

typedef long long ll;

// 求比 n 大、且二进制中 1 的个数与 n 相同的最小数（Gosper 进位）
ll next_same_ones(ll n) {
    ll low = n & -n;      // 最低位的 1，即 2^l
    ll carried = n + low; // 最低位加 1 引发连锁进位：连续 1 段清空，上方第一个 0 位变 1
    // n ^ carried 的置 1 位是被改动的位；>> 2 丢掉新产生的那位，// low 把剩下的 1 折算到最低位
    return carried | (((n ^ carried) >> 2) / low);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);

    ll n;
    while (std::cin >> n && n != 0) { // 输入以 0 结束
        std::cout << next_same_ones(n) << "\n";
    }
    return 0;
}
