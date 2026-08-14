/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-14 14:55
 * update_at: 2026-08-14 14:55
 */
#include <iostream>

const int max_n = 1005;

int memo[max_n];  // memo[x] 记录 ways(x) 的结果，0 表示还没算过

// 以 x 为开头的合法数列数：只留 x 本身，或者再接一个不超过 x/2 的数
int ways(int x) {
    if (memo[x] != 0) {
        return memo[x];
    }
    int total = 1;  // 只有 x 本身这一种最短数列
    for (int nxt = 1; nxt <= x / 2; nxt += 1) {
        total += ways(nxt);
    }
    memo[x] = total;
    return total;
}

int main() {
    int n;
    std::cin >> n;
    std::cout << ways(n) << '\n';
    return 0;
}
