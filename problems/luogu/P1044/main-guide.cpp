/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-14 14:56
 * update_at: 2026-08-14 14:56
 */
#include <iostream>

const int max_n = 20;

int n;
long long memo[max_n][max_n];  // memo[pushed][popped]，-1 表示还没算过

// 已经入栈 pushed 个、出栈 popped 个时，还有多少种方式把剩下的数全部出栈
long long dfs(int pushed, int popped) {
    if (popped == n) {
        return 1;  // 所有数都已出栈，这是唯一一种完成方式
    }
    if (memo[pushed][popped] != -1) {
        return memo[pushed][popped];
    }
    long long total = 0;
    if (pushed < n) {
        total += dfs(pushed + 1, popped);  // 把下一个数入栈
    }
    if (popped < pushed) {
        total += dfs(pushed, popped + 1);  // 栈里有数，弹出一个
    }
    memo[pushed][popped] = total;
    return total;
}

int main() {
    std::cin >> n;
    for (int pushed = 0; pushed <= n; pushed += 1) {
        for (int popped = 0; popped <= n; popped += 1) {
            memo[pushed][popped] = -1;  // 初始都标记为"还没算过"
        }
    }
    std::cout << dfs(0, 0) << '\n';
    return 0;
}
