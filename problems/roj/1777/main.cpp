/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-08 01:55
 * update_at: 2026-10-08 01:55
 */
// 1777《寻找整数》：给定 m, k，求正整数 n 使 (n, 2n] 中恰有 m 个数二进制含 k 个 1。
//
// 关键恒等式（本解的全部依据）：
//   f(n) = #{ x : n < x <= 2n 且 popcount(x) = k }
//        = #{ j : 0 <= j <= n-1 且 popcount(j) = k-1 }。
// 推导：把 (n, 2n] 拆成偶数与奇数。偶数 x = 2y (y <= n) 的 popcount 等于 popcount(y)；
//   奇数 x = 2y+1 的 popcount 等于 popcount(y)+1，且 2y+1 <= 2n 等价于 y <= n-1。
//   于是偶数部分的贡献正是 f(n) 里的「popcount(y) = k」那半边，与 #{(0,n] 中 popcount=k}
//   逐项抵消，只剩奇数部分 #{(0,n) 中 popcount = k-1}，即上面的恒等式。
// 所以 f(n) = m 等价于「恰有 m 个 popcount 为 k-1 的非负整数严格小于 n」。
// 设 a_i 是第 i+1 小（下标 0 起）的「popcount = p」的整数（p = k-1），则
//   m >= 1：n 的取值恰为闭区间 [a_{m-1}+1, a_m]，最小 n = a_{m-1}+1，解的个数 = a_m - a_{m-1}；
//   m == 0：n 的取值恰为 [1, a_0] = [1, 2^p - 1]，最小 n = 1，个数 = 2^p - 1；
//   k == 1：p = 0 时只有 j = 0 一个候选，f(n) 恒等于 1，故 m = 1 有无穷多解（个数记 -1）。
// a_i 用「按二进制位从高到低贪心」求出：本位取 0 时低位有 C(i, 剩余个数) 种填法，
// 与 rank 比较即可决定本位取 0 还是取 1，一次 O(64)。
//
// 复杂度：预处理组合数 O(64^2)；每组询问 2 次 O(64) 贪心 → 单组 O(log n)。
//   t <= 2000 时总计约 2.6e5 次基本运算。空间 O(64^2)。
// 数值范围：n 至多 2^64-1，组合数最大 C(64,32) ≈ 1.83e18，全部用 unsigned long long。

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull; // 答案 n 允许取到 2^64-1，超出 ll 上界，必须用无符号

const int BITS = 64; // 二进制位数上界：题目要求输出的 n 落在 [1, 2^64 - 1]
ull binom[BITS + 1][BITS + 1]; // binom[i][j] = 组合数 C(i, j)，j > i 处保持 0

// 组合数表：数位贪心与无解判定都要反复查，直接按杨辉三角打表
void init_binom() {
    for (int i = 0; i <= BITS; i++) {
        binom[i][0] = 1;
        for (int j = 1; j <= i; j++) {
            binom[i][j] = binom[i - 1][j - 1] + binom[i - 1][j];
        }
    }
}

// 第 rank 小（rank 从 1 起）的「二进制恰有 ones 个 1」的非负整数
ull kth_number(ull rank, int ones) {
    ull x = 0;
    int used = 0;
    for (int i = BITS - 1; i >= 0; i--) {
        // 本位取 0，低位 i 位里还要凑出 need 个 1，方案数就是 C(i, need)
        int need = ones - used;
        ull ways = (need >= 0 && need <= i) ? binom[i][need] : 0ULL;
        if (rank > ways) { // 第 rank 个不在「本位取 0」这一支里
            rank -= ways;
            x |= 1ULL << i;
            used++;
        }
        if (used == ones) break; // 1 已经放满，低位全填 0
    }
    return x;
}

int main() {
    init_binom();
    int t;
    if (scanf("%d", &t) != 1) return 0;
    while (t--) {
        ull m;
        int k;
        if (scanf("%llu %d", &m, &k) != 2) break;
        if (k == 1) { // 候选只剩 j = 0，f(n) 恒为 1
            if (m == 1) printf("1 -1\n");
            else printf("0 0\n"); // 题面保证 10^18 内不会出现
            continue;
        }
        int p = k - 1; // 只需数「popcount = p 且严格小于 n」的整数个数
        if (m == 0) {
            // n 取遍 [1, 2^p - 1]，最小 n 是 1，个数 2^p - 1
            printf("1 %llu\n", (1ULL << p) - 1);
            continue;
        }
        if (binom[BITS][p] < m + 1) { // 2^64 内根本凑不出 m+1 个候选，无解
            printf("0 0\n");
            continue;
        }
        ull prev_big = kth_number(m, p);     // a_{m-1}
        ull next_big = kth_number(m + 1, p); // a_m
        printf("%llu %llu\n", prev_big + 1, next_big - prev_big);
    }
    return 0;
}
