/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-14 14:55
 * update_at: 2026-08-14 14:55
 */
#include <iostream>

const int max_n = 25;

int n, k;
int a[max_n];      // 输入的数字，下标从 1 开始
int chosen[max_n]; // chosen[i] = 1 表示第 i 个数已被选中
int answer = 0;

// x 是素数当且仅当 2..sqrt(x) 都除不尽它
bool is_prime(int x) {
    if (x < 2) {
        return false;
    }
    for (int i = 2; i * i <= x; i += 1) {
        if (x % i == 0) {
            return false;
        }
    }
    return true;
}

// dep: 已经选了几个数；last: 上一个选中的下标；sum: 已选数字的和
void pick(int dep, int last, int sum) {
    if (dep == k) {
        // 选满 k 个数，判断和是否为素数
        if (is_prime(sum)) {
            answer += 1;
        }
        return;
    }
    // 新选的下标必须比 last 大，每个组合只会出现一次；
    // 上界 n - (k - dep) + 1 保证后面还能选满 k - dep 个数
    for (int i = last + 1; i <= n - (k - dep) + 1; i += 1) {
        chosen[i] = 1;
        pick(dep + 1, i, sum + a[i]);
        chosen[i] = 0;  // 回溯恢复，别的组合才能复用这个下标
    }
}

int main() {
    std::cin >> n >> k;
    for (int i = 1; i <= n; i += 1) {
        std::cin >> a[i];
    }
    pick(0, 0, 0);
    std::cout << answer << '\n';
    return 0;
}
