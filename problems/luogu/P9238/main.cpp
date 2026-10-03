/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-02 15:07
 * update_at: 2026-10-02 15:07
 */
/*
 * P9238 [蓝桥杯 2023 省 A] 翻转硬币
 *
 * 结论：最少操作次数 = 1..n 中「无平方因子数」的个数。
 *
 * 记 x_i 表示是否使用一次操作 i（同一个操作用两次等于没用，所以 x_i 只有 0/1）。
 * 硬币 j 最终被翻转的次数是 sum_{i | j} x_i，要求全部朝上：
 *   j = 1 : x_1 = 1
 *   j >= 2: sum_{i | j} x_i = 0 (mod 2)
 * 按 j 从小到大看，第 j 个方程里只出现 x_i (i | j 且 i <= j)，且 x_j 的系数为 1，
 * 于是每个 x_j 都被唯一确定，解正是 x = mu（莫比乌斯函数）。
 * 所以答案 = sum_{i = 1}^{n} [mu(i) != 0] = n 以内无平方因子数的个数。
 *
 * 用容斥（按最小平方因子枚举所有平方数）得到
 *   Q(n) = sum_{d = 1}^{floor(sqrt(n))} mu(d) * floor(n / d^2)。
 * sqrt(n) 最大 1e9，不能直接枚举，于是分成两段：
 *   1) d <= T：线性筛出 mu，直接累加；
 *   2) d >  T：按 q = floor(n / d^2) 分块。q 相同的一段可以批量算，
 *      段内的莫比乌斯和用杜教筛求前缀和 M = sum mu。
 * 取 T = floor(n^(2/5))（并限制在数组容量内），此时块数 Q = floor(n / (T+1)^2)
 * 只有 n^(1/5) 量级，整体复杂度 O(n^(2/5))，n = 1e18 时 0.4s 左右。
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXT = 12000000;      // 阈值上限，约 52MB 内存
static int mu[MAXT + 5];        // 先存 mu(i)，需要时再原地改造成前缀和 M(i)
static int primes[800000];      // 素数表
static unsigned long long notprime[(MAXT >> 6) + 5]; // 合数标记位图
int pcnt;                       // 素数个数
ll T;                           // 直接计算的阈值
unordered_map<ll, ll> memo;     // 杜教筛的记忆化

// 求 floor(sqrt(x))：用 long double 估一个初值，再靠整数运算微调，避免精度问题
ll isqrt_ll(ll x) {
    if (x <= 0) return 0;
    ll r = (ll)sqrtl((long double)x);
    while ((r + 1) <= x / (r + 1)) r++;
    while (r > x / r) r--;
    return r;
}

// 杜教筛：莫比乌斯前缀和 M(x) = sum_{i = 1}^{x} mu(i)
// 由 mu * 1 = eps 得 1 = sum_{d = 1}^{x} M(floor(x / d))，
// 移项就有 M(x) = 1 - sum_{d = 2}^{x} M(floor(x / d))，对 d 整除分块即可
ll mertens(ll x) {
    if (x <= T) return mu[x];               // 小范围查表
    unordered_map<ll, ll>::iterator it = memo.find(x);
    if (it != memo.end()) return it->second;
    __int128 res = 1;                       // sum_{i = 1}^{x} eps(i) = 1
    for (ll d = 2; d <= x; ) {
        ll v = x / d;                       // 这一段的 floor(x / d) 都等于 v
        ll last = x / v;
        res -= (__int128)(last - d + 1) * mertens(v);
        d = last + 1;
    }
    ll rr = (ll)res;                        // M(x) 的绝对值不超过 x，一定放得下
    memo[x] = rr;
    return rr;
}

int main() {
    ll n;
    scanf("%lld", &n);

    // 阈值 T = min(floor(sqrt(n)), floor(n^(2/5)))，并保证不越界
    T = isqrt_ll(n);
    ll t = (ll)powl((long double)n, 0.4L) + 5;
    if (t < T) T = t;
    if (T > MAXT) T = MAXT;
    if (T < 1) T = 1;
    int N = (int)T;

    // 线性筛莫比乌斯函数，此时 mu[i] 就是 mu(i)
    mu[1] = 1;
    for (int i = 2; i <= N; i++) {
        if (!((notprime[i >> 6] >> (i & 63)) & 1ULL)) {
            primes[++pcnt] = i;
            mu[i] = -1;
        }
        for (int j = 1; j <= pcnt; j++) {
            ll v = (ll)primes[j] * i;
            if (v > N) break;
            notprime[v >> 6] |= 1ULL << (v & 63);
            if (i % primes[j] == 0) {
                mu[v] = 0;                  // v 含平方因子
                break;
            }
            mu[v] = -mu[i];
        }
    }

    // 第一段：d <= T 的部分直接累加 mu(d) * floor(n / d^2)
    ll ans = 0;
    for (ll d = 1; d <= T; d++) {
        ans += (ll)mu[d] * (n / (d * d));
    }

    // 把 mu 原地改造成前缀和 M(i)，供杜教筛查表
    for (int i = 1; i <= N; i++) mu[i] += mu[i - 1];

    // 第二段：d > T。此时 floor(n / d^2) = q <= Q，按 q 分块批量算
    ll Q = n / ((T + 1) * (T + 1));
    for (ll q = 1; q <= Q; q++) {
        ll hi = isqrt_ll(n / q);            // floor(n / d^2) >= q 的最大 d
        ll lo = isqrt_ll(n / (q + 1));      // floor(n / d^2) >= q+1 的最大 d
        if (lo < T) lo = T;                 // 只统计 d > T，避免和第一段重复
        // d 在 (lo, hi] 内时 floor(n / d^2) 恰好等于 q，
        // 这些 d 的 mu 之和是 M(hi) - M(lo)，乘上系数 q 累加
        ans += q * (mertens(hi) - mertens(lo));
    }

    printf("%lld\n", ans);
    return 0;
}
