/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-02 15:07
 * update_at: 2026-10-03 11:23
 */
// main.cpp：P9230 [蓝桥杯 2023 省 A] 填空问题 的正式提交程序。
// A 题：位数最多 8 位，统计前后半部分数位和相等的数 —— 按“半长 + 数位和”计数相乘。
// B 题：一共 30 题，统计最终得 70 分（连续答对 7 题）的答题情况数 —— 按“末尾连续答对数”分层递推。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int HALF = 4;          // 1e8 以内偶数位数最多 8 位，所以前/后半部分最多 4 位
const int MAX_SUM = 36;      // 4 位数字的最大数位和是 9*4 = 36
const int MAX_Q = 30;        // 答题总数为 30
const int BRUTE_RUN = 10;    // 连续答对 10 题就是 100 分，到达时立刻停止
const int WANT_RUN = 7;      // 70 分对应的连续答对数

// ways[h][s]：h 位数字（允许前导 0）中数位和为 s 的个数
ll ways[HALF + 1][MAX_SUM + 1];

// 预处理每一位自由取 0~9 的数位和方案数，相当于做 h 次“数位和”背包。
void build_digit_ways() {
    ways[0][0] = 1;
    for (int h = 1; h <= HALF; h++) {
        for (int s = 0; s <= 9 * HALF; s++) {
            ll total = 0;
            for (int d = 0; d <= 9; d++) {
                if (s - d >= 0) {
                    total += ways[h - 1][s - d];
                }
            }
            ways[h][s] = total;
        }
    }
}

// A 题答案：长度为 2h 的数，前 h 位的数位和 == 后 h 位的数位和。
// 后半部分允许前导 0（就是普通的 h 位串），前半部分首位不能是 0。
ll solve_a() {
    build_digit_ways();
    ll ans = 0;
    for (int h = 1; h <= HALF; h++) {
        for (int s = 0; s <= 9 * h; s++) {
            // 前半部分首位不能是 0：先随便填 h 位，再减掉首位为 0 的 h-1 位方案
            ll front = ways[h][s] - ways[h - 1][s];
            ans += front * ways[h][s];
        }
    }
    return ans;
}

// dp[r]：在当前枚举到的长度下，以“末尾恰好连续答对 r 题”结尾、
// 并且中途从未到达 100 分（即从未连续答对 10 题）的答题序列数。
ll dp[BRUTE_RUN + 1];

// B 题答案：对每个长度 t，恰好结束在 70 分（末尾连续答对 7 题）的序列都要计入。
ll solve_b() {
    ll ans = 0;
    dp[0] = 1;
    for (int t = 1; t <= MAX_Q; t++) {
        ll ndp[BRUTE_RUN + 1];
        for (int r = 0; r <= BRUTE_RUN; r++) {
            ndp[r] = 0;
        }
        ll all = 0;                       // 所有长度 t-1 的合法序列，下一题答错后都落到 r = 0
        for (int r = 0; r <= BRUTE_RUN; r++) {
            all += dp[r];
        }
        ndp[0] = all;
        for (int r = 0; r + 1 < BRUTE_RUN; r++) {
            ndp[r + 1] += dp[r];          // 下一题答对，连续答对数加一；到 10 就已经是 100 分，不再延伸
        }
        for (int r = 0; r <= BRUTE_RUN; r++) {
            dp[r] = ndp[r];
        }
        ans += dp[WANT_RUN];
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    char pid;
    if (!(cin >> pid)) {
        return 0;
    }
    if (pid == 'A') {
        cout << solve_a() << "\n";
    } else {
        cout << solve_b() << "\n";
    }
    return 0;
}
