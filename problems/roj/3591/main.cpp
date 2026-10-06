/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 14:42
 * update_at: 2026-10-06 14:42
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MOD = 10007;
const int MAXK = 1005;

// 题目输入：a, b 为底数，k 为次数，n + m = k
ll a, b, k, n, m;

ll c[MAXK][MAXK]; // c[i][j] = C(i, j) mod 10007，杨辉三角递推求出

// 快速幂：返回 (base ^ exp) mod MOD，用来算 a^n 和 b^m
ll fast_pow(ll base, ll exp) {
    ll result = 1;
    base %= MOD;
    while (exp > 0) {
        if (exp & 1) {
            result = result * base % MOD;
        }
        base = base * base % MOD;
        exp >>= 1;
    }
    return result;
}

// 用杨辉三角递推出 C(i, j) 对 MOD 取模的值，避免直接算大数或做除法
void build_comb() {
    for (int i = 0; i <= k; i++) {
        c[i][0] = 1;
        c[i][i] = 1;
        for (int j = 1; j < i; j++) {
            c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % MOD;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> a >> b >> k >> n >> m;

    build_comb();

    // 二项式定理：x^n y^m 的系数 = C(k, n) * a^n * b^m
    ll ans = c[k][n] * fast_pow(a, n) % MOD * fast_pow(b, m) % MOD;
    cout << ans << endl;

    return 0;
}
