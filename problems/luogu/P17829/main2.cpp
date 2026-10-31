/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-31 19:50
 * update_at: 2026-10-31 19:50
 */
// main2.cpp：把 m 钉成四个具体取值来拿部分分，覆盖 m = 1、m = 2、m = n、m = n - 1。
// 其余 m 这一份代码不给答案，直接输出 0。
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
    for (int i = 1; i <= n; ++i)
        for (int j = i + 1; j <= n; ++j) best = max(best, a[i] & a[j]);
    return best;
}

// m = n - 1：恰好丢掉一个数。先算全体与 base，再逐位看这一位是不是只被一个数否决
int solve_drop_one() {
    int base = a[1];
    for (int i = 2; i <= n; ++i) base &= a[i];
    for (int i = 1; i <= n; ++i) extra[i] = 0;

    // 第 b 位上为 0 的数如果恰好只有第 who 个，那么丢掉 who 就能把这一位补回来
    for (int b = 0; b < 30; ++b) {
        int zero_cnt = 0, who = 0;
        for (int i = 1; i <= n; ++i)
            if (((a[i] >> b) & 1) == 0) {
                ++zero_cnt;
                who = i;
            }
        if (zero_cnt == 1) extra[who] |= 1 << b;
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
    // 其余 m 在二分点上没有对应的特判做法，这一支不做处理

    cout << ans << '\n';
    return 0;
}
