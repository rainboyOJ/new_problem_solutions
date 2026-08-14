/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-14 14:55
 * update_at: 2026-08-14 14:55
 */
#include <iostream>

int n, k;
int answer = 0;

// dep: 已经分好的份数；last: 上一份的大小；left: 还剩下没分的数
// 每一份都不小于上一份（单调不减），保证 (1,2,4) 和 (4,2,1) 只算一次
void divide(int dep, int last, int left) {
    if (dep == k - 1) {
        // 最后一份直接把剩下的数取走，只要它不小于上一份
        if (left >= last) {
            answer += 1;
        }
        return;
    }
    // 之后还剩 k - dep 份，每份都不小于 value，
    // 所以 value 最多到 left / (k - dep)，再大就凑不满剩下的份数
    for (int value = last; value * (k - dep) <= left; value += 1) {
        divide(dep + 1, value, left - value);
    }
}

int main() {
    std::cin >> n >> k;
    divide(0, 1, n);  // 还没分任何一份，上一份当作 1，保证每份都是正整数
    std::cout << answer << '\n';
    return 0;
}
