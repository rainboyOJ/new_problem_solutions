/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-31 19:50
 * update_at: 2026-11-02 09:20
 */
// main2.cpp：部分分解法，只处理 m = 1、m = 2、m = n、m = n - 1。
// 其他 m 不在这份代码的适用范围内，会输出 0。
#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5 + 5;
int n, m;
int a[maxn];      // a_i < 2^30，int 足够
int extra[maxn];  // extra[i]：只丢掉第 i 个数时能额外补回来的位

// m = 1：任选一个数，答案就是最大值
int solve_m1() {
    int best = 0;
    for (int i = 1; i <= n; ++i) best = max(best, a[i]);
    return best;
}

// m = n：全部数都要选，答案就是全体按位与
int solve_full() {
    int cur = a[1];
    for (int i = 2; i <= n; ++i) cur &= a[i];
    return cur;
}

// m = 2：直接枚举所有数对
int solve_m2() {
    int best = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            best = max(best, a[i] & a[j]);
        }
    }
    return best;
}

// m = n - 1：恰好丢掉一个数，只有某一位恰好有一个 0 时，才能把它补成 1。
int solve_drop_one() {
    int base = a[1];
    for (int i = 2; i <= n; ++i) base &= a[i];
    for (int i = 1; i <= n; ++i) extra[i] = 0;

    // zero_cnt 统计第 b 位为 0 的数的个数，zero_pos 记录其中一个的下标。
    for (int b = 0; b < 30; ++b) {
        int zero_cnt = 0, zero_pos = 0;
        for (int i = 1; i <= n; ++i) {
            if (((a[i] >> b) & 1) == 0) {
                ++zero_cnt;
                zero_pos = i;
            }
        }
        if (zero_cnt == 1) extra[zero_pos] |= 1 << b;
    }

    // 丢掉第 i 个数得到的答案就是 base | extra[i]，取最大
    int best = 0;
    for (int i = 1; i <= n; ++i) best = max(best, base | extra[i]);
    return best;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> a[i];

    int ans = 0;
    if (m == 1) ans = solve_m1();
    else if (m == n) ans = solve_full();
    else if (m == 2) ans = solve_m2();
    else if (m == n - 1) ans = solve_drop_one();
    // 其余 m 没有对应分支，ans 保持为 0。

    cout << ans << '\n';
    return 0;
}
