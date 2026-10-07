/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-08 03:20
 * update_at: 2026-10-08 03:20
 */
// main.cpp：简单的期望（roj 1785）。
// 题意校正：题面【题目描述】写的 "x = x/2" 是排版笔误，三个官方样例只有 x = x*2 能同时对上
//   （1 1 50 -> 1.0；5 3 0 -> 3.0；5 3 25 -> 1.921875 = 123/64），本题按 x = x*2 实现。
// 目标：最终值 w 的 v2(w)（质因数分解中 2 的指数，即二进制末尾 0 的个数）的期望。
//
// 状态设计（低位精确 + 高位游程摘要）：
//   取 s = w mod 2^B（低 B 位精确），t = w 的第 B 位，k = 从第 B 位起连续等于 t 的位数。
//   * w != 0 时 v2(w) 由状态直接读出：s != 0 -> v2(s)；s = 0 且 t = 1 -> B；s = 0 且 t = 0 -> B + k。
//   * w += 1：s < 2^B - 1 时 (t,k) 不变；s = 2^B - 1 时 s 归零、进位进入第 B 位：
//       t = 1（第 B 位起是 k 个 1，第 B+k 位是 0）-> 进位穿过这 k 个 1，游程变成 k 个 0，k 不变；
//       t = 0 -> 第 B 位由 0 变 1，游程重置为 1。
//   * w *= 2：s 左移一位、旧的 bit(B-1) 进入第 B 位；该位等于 t 则游程延续 k+1，否则重置为 1。
//
// 关键压缩：三种转移对 k 都是仿射的（k' = k、k + 1 或常数 1），所以对每个 (s,t) 只需维护
//   p = Σ_k Pr[s][t][k]，q = Σ_k k·Pr[s][t][k]，
// 状态数从 O(2^B · n) 降到 O(2^B)，答案照样能还原（s = 0 且 t = 0 时贡献 B·p + q）。
//
// 摘要为何够用：摘要丢掉的只是"第 B+k 位之上"的信息，只有 w += 1 的进位穿过整段 1 游程、
//   且第 B+k 位实际是 1 时才会用到它。这种"假信息"要再从 s = 0 走到 s = 2^B - 1（途中不能用
//   w *= 2，否则游程立即重置、摘要自动修正）需要 2^B - 1 步，B = 12 时是 4095 步，
//   n <= 200 留有 20 倍余量，故本实现与精确解一致。
// 复杂度：O(n · 2^B) 时间，O(2^B) 空间；B = 12、n = 200 时约 1.6e6 次转移。

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int B = 12;          // 低 B 位精确记录，高位只留 (t,k) 摘要
const int SZ = 1 << B;     // 低 B 位的取值个数
const int MASK = SZ - 1;   // 低 B 位全 1，用于判断进位

// 每个 (s,t) 上聚合两个量：p = 该状态的概率总和，q = Σ_k k·Pr[s][t][k]
struct Agg {
    double p;
    double q;
};
Agg cur[2][SZ];  // cur[t][s]
Agg nxt[2][SZ];  // 本步转移的落点

// v2(v) = v 的二进制末尾 0 的个数（v >= 1）
int v2(ll v) {
    int z = 0;
    for (; (v & 1) == 0; v >>= 1) z++;
    return z;
}

int main() {
    ll x = 0;
    int n = 0, p = 0;
    if (scanf("%lld %d %d", &x, &n, &p) != 3) return 0;

    // 初始状态：低 B 位取 x，第 B 位是 t0，游程是 hi = x >> B 从最低位起连续等于 t0 的位数
    int s0 = x & MASK;
    ll hi = x >> B;
    int t0 = hi & 1;
    int k0 = 0;
    for (ll h = hi; h > 0 && (h & 1) == t0; h >>= 1) k0++;
    if (k0 == 0) k0 = 1;  // x < 2^B 时高位全是 0，按"第 B 位起是 1 个 0"记

    cur[t0][s0].p = 1.0;
    cur[t0][s0].q = k0;

    double mul2 = p / 100.0;      // w *= 2 的概率
    double add1 = 1.0 - mul2;     // w += 1 的概率

    for (int step = 0; step < n; step++) {
        for (int t = 0; t < 2; t++)
            for (int s = 0; s < SZ; s++) {
                nxt[t][s].p = 0.0;
                nxt[t][s].q = 0.0;
            }

        for (int t = 0; t < 2; t++) {
            for (int s = 0; s < SZ; s++) {
                double pr = cur[t][s].p;
                if (pr == 0.0) continue;  // 概率为 0 的分支（p = 0 或 100）直接跳过
                double qk = cur[t][s].q;

                if (add1 > 0.0) {  // 操作一：w += 1
                    double w1 = pr * add1;
                    if (s != MASK) {
                        nxt[t][s + 1].p += w1;
                        nxt[t][s + 1].q += qk * add1;
                    } else {
                        int nt = t ^ 1;  // 进位进入第 B 位，该位取反
                        nxt[nt][0].p += w1;
                        // t=1 时游程原样变 0（k 不变），t=0 时第 B 位由 0 变 1（k 重置为 1）
                        nxt[nt][0].q += (t == 1) ? qk * add1 : w1;
                    }
                }

                if (mul2 > 0.0) {  // 操作二：w *= 2
                    double w2 = pr * mul2;
                    int bit = (s >> (B - 1)) & 1;  // 左移后进入第 B 位的那一位
                    int ns = (s << 1) & MASK;
                    if (bit == t) {  // 与第 B 位相同，游程延续：k' = k + 1
                        nxt[t][ns].p += w2;
                        nxt[t][ns].q += qk * mul2 + w2;
                    } else {  // 不同，游程重置：k' = 1
                        nxt[bit][ns].p += w2;
                        nxt[bit][ns].q += w2;
                    }
                }
            }
        }

        for (int t = 0; t < 2; t++)
            for (int s = 0; s < SZ; s++) cur[t][s] = nxt[t][s];
    }

    // 统计答案：s != 0 贡献 v2(s)；s = 0 且 t = 1 贡献 B；s = 0 且 t = 0 贡献 B + k
    double ans = 0.0;
    for (int s = 1; s < SZ; s++)
        ans += v2(s) * (cur[0][s].p + cur[1][s].p);
    ans += B * (cur[0][0].p + cur[1][0].p) + cur[0][0].q;

    printf("%.10f\n", ans);
    return 0;
}
