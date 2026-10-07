/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 00:55
 * update_at: 2026-10-06 00:55
 */

#include <cstdio>

typedef long long ll;

const ll P = 2333;            // 模数，题目给定的质数
const ll MOD = 2333;

// C[n][m]：模 2333 意义下的组合数表，n, m < 2333
// S[n][m]：组合数表第 n 行的前缀和 S(n, m) = sum_{i=0}^{m} C(n, i) mod 2333
// 值都小于 2333，用 int 控制内存（两张表共约 44MB）
int C[P][P];
int S[P][P];

// 预处理杨辉三角组合数表与行前缀和表（i 从 0 开始，第 0 行也要填）
void init() {
    for (ll i = 0; i < P; i++) {
        C[i][0] = 1;
        S[i][0] = 1;
        for (ll j = 1; j <= i; j++)
            C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % MOD;
        // 第 i 行 C(i, j) 在 j > i 时为 0，前缀和保持不变
        for (ll j = 1; j < P; j++) {
            if (j <= i)
                S[i][j] = (S[i][j - 1] + C[i][j]) % MOD;
            else
                S[i][j] = S[i][i];
        }
    }
}

// Lucas 定理求 C(n, m) mod 2333
ll lucas(ll n, ll m) {
    if (m == 0) return 1;
    if (n < m) return 0;
    if (n < P && m < P) return C[n][m];
    return lucas(n / P, m / P) * C[n % P][m % P] % MOD;
}

// 求 S(n, k) = sum_{i=0}^{k} C(n, i) mod 2333
// 按 i = j*p + r 分块：完整块贡献 S(n%P, P-1) * S(n/P, k/P-1)，
// 散块（j = k/P，r 只到 k%P）贡献 C(n/P, k/P) * S(n%P, k%P)
ll query_sum(ll n, ll k) {
    if (k < 0) return 0;
    if (n < P && k < P) return S[n][k];
    ll full = S[n % P][P - 1] * query_sum(n / P, k / P - 1) % MOD;
    ll part = lucas(n / P, k / P) * S[n % P][k % P] % MOD;
    return (full + part) % MOD;
}

int main() {
    init();
    ll t;
    scanf("%lld", &t);
    while (t--) {
        ll n, k;
        scanf("%lld%lld", &n, &k);
        printf("%lld\n", query_sum(n, k));
    }
    return 0;
}
