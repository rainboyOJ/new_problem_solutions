/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-08 04:27
 * update_at: 2026-10-08 04:27
 */
// main.cpp：区间计数。把"V = x * D(x)"整形成若干同余数列的并集，每组用等差数列
// 计数、两组重叠用容斥扣掉，单次询问 O(1)。
// 与 main.py 同一算法：同一张同余式表，同样只做加减与整除。
//
// 数根性质：x >= 1 时 D(x) = k (1 <= k <= 9) 等价于 x ≡ k (mod 9)（余 0 记 9）。
// 固定 k 后 V = x * k，把 x = 9m + k (m >= 0) 代入得 V = 9k*m + k^2，即
//   k=1 -> V ≡ 1  (mod 9)     k=2 -> V ≡ 4  (mod 18)    k=3 -> V ≡ 9  (mod 27)
//   k=4 -> V ≡ 16 (mod 36)    k=5 -> V ≡ 25 (mod 45)    k=6 -> V ≡ 36 (mod 54)
//   k=7 -> V ≡ 49 (mod 63)    k=8 -> V ≡ 64 (mod 72)    k=9 -> V ≡ 0  (mod 81)
// 这九族按 V mod 9 归并（平方剩余只有 0/1/4/7，其余余数不可能出现）：
//   mod 9 == 1：k=1 一族就是全部，k=8 被它包含，丢弃；
//   mod 9 == 4：k=2 与 k=7 的并集，交集 V ≡ 112 (mod 126) 要扣一次；
//   mod 9 == 7：k=4 与 k=5 的并集，交集 V ≡ 160 (mod 180) 要扣一次；
//   mod 9 == 0：k=3 的 {V ≡ 9 (mod 27)} 与 k=9 的 {81 | V}，两者互斥；
//               k=6 的 V ≡ 36 (mod 54) 完全落在 V ≡ 9 (mod 27) 里，丢弃。
// 于是答案 = 表里各族等差数列项数的带符号求和，前缀相减得到区间计数。

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// 一族同余式对应一条等差数列：first 是它的最小正解，mod 是公差，
// sign 是该族在容斥中的系数（交集项为 -1）。
struct Term {
    ll first;
    ll mod;
    int sign;
};

const int TERM_CNT = 9; // 归并后剩下的同余式族数（含两条容斥负项）

// 首项必须写成最小正解：81 | V 的首项是 81 而不是 0，否则会把 V = 0 数进来。
const Term TERMS[TERM_CNT] = {
    {1, 9, 1},      // k=1，也是整个 mod 9 == 1 类
    {4, 18, 1},     // k=2
    {49, 63, 1},    // k=7
    {16, 36, 1},    // k=4
    {25, 45, 1},    // k=5
    {9, 27, 1},     // k=3，也覆盖 k=6
    {81, 81, 1},    // k=9（81 | V）
    {112, 126, -1}, // k=2 与 k=7 的重叠部分
    {160, 180, -1}, // k=4 与 k=5 的重叠部分
};

// [1, n] 中满足 V ≡ t.first (mod t.mod) 的正整数个数
ll cntResidue(ll n, const Term &t) {
    if (n < t.first) return 0;       // 这一族一个都没有，且避免负数进除法
    return (n - t.first) / t.mod + 1; // 首项 first、公差 mod 的等差数列项数
}

// [1, n] 中"小D喜欢的数"的个数
ll countUpto(ll n) {
    ll res = 0;
    for (int i = 0; i < TERM_CNT; ++i) {
        res += (ll)TERMS[i].sign * cntResidue(n, TERMS[i]);
    }
    return res;
}

int main() {
    int T;
    if (scanf("%d", &T) != 1) return 0;
    while (T--) {
        ll L, R;
        if (scanf("%lld %lld", &L, &R) != 2) break;
        printf("%lld\n", countUpto(R) - countUpto(L - 1)); // L = 1 时传 0 进去，前缀为 0
    }
    return 0;
}
