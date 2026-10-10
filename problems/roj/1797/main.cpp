// 1797 K维斐波那契
// 一本通·高手训练（数学基础）  https://roj.ac.cn/problem/1797
//
// 题意：F(1)=F(2)=1, F(i)=F(i-1)+F(i-2)。
//   k 维超立方体 A 每维 1..n，A(i_1..i_k) = F(i_1+...+i_k-k+1)，
//   求 A 内全部 n^k 个元素之和对 1e9+7 取模。多组询问 T<=100，n,k<=1e9。
//
// 算法（矩阵快速幂，O(log n + log k)/组）：
//   令 M = [[1,1],[1,0]]，则 M^m = [[F(m+1),F(m)],[F(m),F(m-1)]]，
//   于是 A 中元素 F(1+Σ(i_j-1)) = (M^{Σ(i_j-1)})_{11}。
//   把 k 重求和拆开，因为 M 的各次幂彼此可交换：
//       Σ_{i_1..i_k} M^{Σ(i_j-1)} = (Σ_{j=0}^{n-1} M^j)^k = P^k
//   取 (1,1) 元素即答案。P 用前缀和公式 Σ_{r=1}^{x}F(r)=F(x+2)-1 化简为
//       P = [[F(n+2)-1, F(n+1)-1], [F(n+1)-1, F(n)]]
//   先求 M^n 得到 F(n)、F(n+1)，再加出 F(n+2)，最后求 P^k 取左上角。
//
// 坑：F(n+2)-1、F(n+1)-1 可能取到 0，做减法要先 +MOD 再取模；矩阵乘法全程 ll。

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007LL;

// 2x2 矩阵，全局结构体便于传参
struct Mat {
    ll a[2][2];
};

// 模意义下的 2x2 矩阵乘法
Mat mul(const Mat &x, const Mat &y) {
    Mat r;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            ll s = 0;
            for (int t = 0; t < 2; t++) {
                s = (s + x.a[i][t] * y.a[t][j]) % MOD;
            }
            r.a[i][j] = s;
        }
    }
    return r;
}

// 2x2 矩阵快速幂，指数 e 可达 1e9
Mat mpow(Mat base, ll e) {
    Mat res;                    // 单位矩阵
    res.a[0][0] = 1; res.a[0][1] = 0;
    res.a[1][0] = 0; res.a[1][1] = 1;
    while (e > 0) {
        if (e & 1LL) res = mul(res, base);
        base = mul(base, base);
        e >>= 1;
    }
    return res;
}

// 单组询问：n 为每维长度，k 为维数
ll solve(ll n, ll k) {
    Mat M;                      // 斐波那契转移矩阵
    M.a[0][0] = 1; M.a[0][1] = 1;
    M.a[1][0] = 1; M.a[1][1] = 0;

    Mat Mn = mpow(M, n);        // M^n = [[F(n+1),F(n)],[F(n),F(n-1)]]
    ll fn = Mn.a[0][1];         // F(n)
    ll fn1 = Mn.a[0][0];        // F(n+1)
    ll fn2 = (fn1 + fn) % MOD;  // F(n+2) = F(n+1) + F(n)

    Mat P;                      // P = Σ_{j=0}^{n-1} M^j
    P.a[0][0] = (fn2 - 1 + MOD) % MOD;
    P.a[0][1] = (fn1 - 1 + MOD) % MOD;
    P.a[1][0] = (fn1 - 1 + MOD) % MOD;
    P.a[1][1] = fn % MOD;

    Mat R = mpow(P, k);         // k 维求和 = P 的 k 次方
    return R.a[0][0];
}

int main() {
    int T;
    if (scanf("%d", &T) != 1) return 0;
    while (T--) {
        ll n, k;
        scanf("%lld %lld", &n, &k);
        printf("%lld\n", solve(n, k));
    }
    return 0;
}
