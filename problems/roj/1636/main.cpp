/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 23:47
 * update_at: 2026-10-05 23:47
 */
// 一本通 6.4 例 6 计算器：p 为质数，三问分治。
// 任务 1 快速幂；任务 2 费马小定理求逆元解线性同余方程；任务 3 BSGS 求最小离散对数。
#include <cstdio>
#include <map>
#include <cmath>

typedef long long ll;

ll y, z, p; // 每组询问的三个数

// 快速幂 a^b % mod，乘法时先转 __int128 防止溢出（a,b < 1e9，相乘达 1e18 超出 ll 安全范围不大但稳妥）
ll qpow(ll a, ll b, ll mod) {
    ll res = 1 % mod; // mod 可能为 1，答案取 0
    a %= mod;
    while (b > 0) {
        if (b & 1) res = (__int128)res * a % mod;
        a = (__int128)a * a % mod;
        b >>= 1;
    }
    return res;
}

// 任务 2：求最小非负 x 满足 x * y ≡ z (mod p)，p 是质数
void solve2() {
    if (y % p == 0) {
        // 左边恒为 0：z ≡ 0 时任何 x 都是解，最小取 0；否则无解
        if (z % p == 0)
            printf("0\n");
        else
            printf("Orz, I cannot find x!\n");
        return;
    }
    // gcd(y, p) = 1，费马小定理：逆元为 y^(p-2)
    ll inv = qpow(y, p - 2, p);
    printf("%lld\n", z % p * inv % p);
}

// 任务 3：求最小非负 x 满足 y^x ≡ z (mod p)，BSGS 大步小步
void solve3() {
    if (z % p == 1 % p) {
        // y^0 = 1，x = 0 是最小解（p=1 时 z%1=0=1%1 同理）
        printf("0\n");
        return;
    }
    if (y % p == 0) {
        // x >= 1 时 y^x ≡ 0，只有 z ≡ 0 有解且最小为 1
        if (z % p == 0)
            printf("1\n");
        else
            printf("Orz, I cannot find x!\n");
        return;
    }
    // 此时 gcd(y, p) = 1，y^m 可逆，可安全移项
    // x = i*m - j：小步枚举 j 存 z*y^j，大步枚举 i 查 y^(i*m)
    ll m = (ll)sqrt((double)(p - 1)) + 1; // 块长约 sqrt(p)
    std::map<ll, ll> baby; // baby[v] = 使 z*y^j ≡ v 的最大 j（j 越大 x 越小）
    ll cur = z % p;        // cur = z * y^j % p
    for (ll j = 0; j < m; ++j) {
        baby[cur] = j;     // 顺序写入，同值后被更大的 j 覆盖
        cur = (__int128)cur * y % p;
    }
    ll step = qpow(y, m, p);      // 大步长 y^m
    ll giant = 1;                 // giant = y^(i*m) % p
    for (ll i = 1; i <= m + 1; ++i) { // 覆盖 x ∈ [0, p-1] 的全部取值
        giant = (__int128)giant * step % p;
        if (baby.find(giant) != baby.end()) {
            printf("%lld\n", i * m - baby[giant]);
            return;
        }
    }
    printf("Orz, I cannot find x!\n");
}

int main() {
    int T, K;
    scanf("%d %d", &T, &K);
    for (int t = 1; t <= T; ++t) {
        scanf("%lld %lld %lld", &y, &z, &p);
        if (K == 1)
            printf("%lld\n", qpow(y, z, p));
        else if (K == 2)
            solve2();
        else
            solve3();
    }
    return 0;
}
