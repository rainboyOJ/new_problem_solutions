// 1813 图的计数
// 一本通·高手训练 六、数学基础  同源题：JZOJ 3085【NOIP2012模拟11.3】图的计数
//
// 题意：统计 n 个点、m 条边的有向图（允许重边、自环）的个数，要求 1 号点到 n 号点
//       的最短路径长度 >= n-1（有解时即恰好 = n-1），答案 mod 1e9+7。
//
// 关键结论（推导见 index.md）：
//   设 1 = u_0 -> u_1 -> ... -> u_{n-1} = n 是一条长度为 n-1 的最短路，则它必经全部 n 个点。
//   固定这个顶点顺序后，允许的边类型只有：
//     · n-1 条链边 u_i -> u_{i+1}（每条至少 1 条，否则到不了 n）
//     · 全部反向边/自环（i >= j 的对），它们走回头路，绝不会缩短最短路
//   禁止的是 "捷径边" u_i -> u_j (j >= i+2)，共 C(n-1,2) 种，会让最短路变短。
//   中间 n-2 个点可任意排列，故乘 (n-2)!；不同排列对应的图集互不相交，直接累加即可。
//   余下 k = m-n+1 条边自由投到 A = n^2 - C(n-1,2) = (n^2+3n-2)/2 种允许类型里，
//   隔板法（可重组合）给出 C(A+k-1, k)。
//
//   答案 = (n-2)! * C(A + m - n, m - n + 1)  (mod 1e9+7)
//   特判：n = 1 -> 1；m < n-1 (n >= 2) -> 0。
//
// 复杂度：O(n + m) 时间（阶乘 + k 个因子 + 一次快速幂），O(1) 空间。

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007LL;  // 1e9+7

// 题目规模不大，直接开全局数组存阶乘相关（本题其实只需常数网格）
const int MAXN = 10005;

ll fact[MAXN];  // fact[i] = i! mod MOD

// 快速幂：求 x^b mod MOD
ll power(ll x, ll b) {
    ll res = 1;
    x %= MOD;
    while (b > 0) {
        if (b & 1) res = res * x % MOD;
        x = x * x % MOD;
        b >>= 1;
    }
    return res;
}

// 组合数 C(N, K) mod MOD（本题 N < MOD，逐因子乘 + 费马小定理求逆元）
ll comb(ll N, ll K) {
    if (K < 0 || K > N) return 0;
    if (K > N - K) K = N - K;  // 取小的一侧，减少循环次数
    ll num = 1, den = 1;
    for (ll i = 0; i < K; i++) {
        num = num * ((N - i) % MOD) % MOD;  // 分子：N * (N-1) * ... * (N-K+1)
        den = den * ((i + 1) % MOD) % MOD;  // 分母：K!
    }
    return num * power(den, MOD - 2) % MOD;
}

int main() {
    ll n, m;
    if (scanf("%lld %lld", &n, &m) != 2) return 0;

    // 特判 1：n = 1，起点即终点，距离恒为 0 = n-1，m 条边只能全是自环 -> 唯一图
    if (n == 1) {
        printf("1\n");
        return 0;
    }

    // 特判 2：边不够连成 n 个点的链，无解
    if (m < n - 1) {
        printf("0\n");
        return 0;
    }

    // 阶乘：(n-2)!
    fact[0] = 1;
    for (int i = 1; i <= n; i++) fact[i] = fact[i - 1] * i % MOD;

    // 允许的边类型数 A = n^2 - C(n-1, 2)
    ll A = n * n - (n - 1) * (n - 2) / 2;
    ll k = m - n + 1;  // 剩余自由分配的边数

    ll ans = fact[n - 2] * comb(A + k - 1, k) % MOD;
    printf("%lld\n", ans);
    return 0;
}
