/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-04 21:49
 * update_at: 2026-10-04 21:49
 */
// main.cpp：最小操作次数 = ΣΩ(a_i) - n·Ω(gcd)
// 每次操作“留一个数不变、其余乘素数”，把第 i 个数额外乘上的素数记为 q_i 的因子，
// 所有数最终相等等价于每个 a_i / (q_i) 都等于同一个公因数 C。
// 取 C = g = gcd 最优，于是答案就是每个 a_i 去掉 g 的质因子后，剩下的质因子个数之和。
// 用筛法预处理 Ω 表：质数幂 p^k 给它的每个倍数贡献 1，再单遍扫描累加即可。

#include <cstdio>

typedef long long ll;

const int MAX_A = 1000000; // 题面数据范围里 a_i 的上限

int omega[MAX_A + 1]; // omega[v] = v 的质因数个数（计重数），只有 0~20 级别，用 int 即可

// 筛法预处理 Ω 表：对每个质数 p，其幂 p^k（p^k <= MAX_A）给所有 p^k 的倍数多贡献一个质因子。
void build_omega() {
    for (int p = 2; p <= MAX_A; p++) {
        if (omega[p] != 0) {
            continue; // 合数已被更小的质数标记过，p 不是质数
        }
        for (int power = p; power <= MAX_A; ) {
            for (int multiple = power; multiple <= MAX_A; multiple += power) {
                omega[multiple]++;
            }
            if (power > MAX_A / p) {
                break; // 再乘一次 p 就超过值域上限，直接结束，避免 int 溢出
            }
            power *= p;
        }
    }
}

ll gcd(ll a, ll b) {
    while (b != 0) {
        ll t = a % b;
        a = b;
        b = t;
    }
    return a;
}

int main() {
    build_omega();

    ll n;
    if (scanf("%lld", &n) != 1) {
        return 0;
    }

    // 边读边累加 ΣΩ(a_i) 与全体 a_i 的 gcd，不保存整个序列
    ll sum_omega = 0;
    ll common = 0;
    for (ll i = 1; i <= n; i++) {
        ll value;
        if (scanf("%lld", &value) != 1) {
            break;
        }
        sum_omega += omega[value];
        common = gcd(common, value);
    }

    printf("%lld\n", sum_omega - n * omega[common]);
    return 0;
}
