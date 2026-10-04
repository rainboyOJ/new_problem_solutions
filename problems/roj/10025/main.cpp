/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-04 23:13
 * update_at: 2026-10-04 23:13
 */
// main.cpp：k 进制 l~r 位数中数位和被 4/5/6 整除的数的个数（模 1e9+7）。
// 思路：答案 = G(r) - G(l-1)，G(n) 为 [0,k^n) 中合法数的个数；
// 判定只看数位和模 lcm(4,5,6)=60，一步转移是模 60 的循环卷积，
// 层数到 1e18，用卷积快速幂（循环矩阵性质，每层 O(60^2)）跨过去。

#include <cstdio>

typedef long long ll;

const ll MOD = 1000000007LL;
const int M = 60; // lcm(4,5,6)，数位和模 60 即可判定合法性

// 计数器按数位和模 60 的余数保存分布，固定 60 项，全局数组
ll dist[M];       // 当前分布：dist[i] = 数位和 ≡ i (mod 60) 的串数
ll base_dist[M];  // 快速幂中不断平方的底向量
ll result_dist[M]; // 快速幂累乘的结果向量
ll tmp_dist[M];   // 卷积结果的临时数组

ll l, r, k; // 输入：位数区间 [l,r]，进制 k（都可能到 1e18）

// 两个「数位和模 60 分布」做循环卷积，结果存到 out
void conv(ll a[], ll b[], ll out[]) {
    for (int i = 0; i < M; ++i) out[i] = 0;
    for (int i = 0; i < M; ++i) {
        if (a[i] == 0) continue; // 空档跳过，省内层循环
        for (int j = 0; j < M; ++j) {
            if (b[j] == 0) continue;
            int pos = i + j;
            if (pos >= M) pos -= M; // 模 60，用减法代替取模更快
            out[pos] = (out[pos] + a[i] * b[j]) % MOD;
        }
    }
}

// 初始分布 src 自卷 n 次（快速幂），结果存回 src
void pow_dist(ll src[], ll n) {
    // 结果向量置为单位元：0 位、数位和为 0
    for (int i = 0; i < M; ++i) result_dist[i] = 0;
    result_dist[0] = 1;
    for (int i = 0; i < M; ++i) base_dist[i] = src[i];
    while (n > 0) {
        if (n & 1) {
            conv(result_dist, base_dist, tmp_dist);
            for (int i = 0; i < M; ++i) result_dist[i] = tmp_dist[i];
        }
        conv(base_dist, base_dist, tmp_dist);
        for (int i = 0; i < M; ++i) base_dist[i] = tmp_dist[i];
        n >>= 1;
    }
    for (int i = 0; i < M; ++i) src[i] = result_dist[i];
}

// 恰好 n 位（允许前导零）的 k 进制数里，数位和被 4/5/6 整除的个数
ll count_good(ll n) {
    // 生成一位数字的余数分布 step：每个数字 d (0<=d<k) 贡献 d mod 60，
    // 每个余数先摊 k/60 个，余下前 k%60 个余数各再多一个
    ll step[M];
    ll quota = k / M, extra = k % M;
    for (int i = 0; i < M; ++i) step[i] = quota + (i < extra ? 1 : 0);
    pow_dist(step, n);
    // 合法余数集合：被 4 或 5 或 6 整除的 i (0<=i<60)，共 28 个
    ll sum = 0;
    for (int i = 0; i < M; ++i)
        if (i % 4 == 0 || i % 5 == 0 || i % 6 == 0)
            sum = (sum + step[i]) % MOD;
    return sum;
}

int main() {
    scanf("%lld %lld %lld", &l, &r, &k);
    // l 位数到 r 位数 = 数值在 [k^(l-1), k^r)；高位补零不改数位和，
    // 答案 = 恰好 r 位的合法个数 - 恰好 l-1 位的合法个数（l=1 时减去数值 0）
    ll ans = (count_good(r) - count_good(l - 1) % MOD + MOD) % MOD;
    printf("%lld\n", ans);
    return 0;
}
