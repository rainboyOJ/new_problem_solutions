#include <iostream>

using namespace std;

const int MOD = 1e9 + 7;

// 快速幂求逆元
long long qpow(long long a, long long b) {
    long long res = 1;
    while (b) {
        if (b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

// 计算组合数 C(n, k)
long long C(int n, int k) {
    if (k < 0 || k > n) return 0;
    long long num = 1, den = 1;
    for (int i = 1; i <= k; ++i) {
        num = num * (n - i + 1) % MOD;
        den = den * i % MOD;
    }
    return num * qpow(den, MOD - 2) % MOD;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    // 翻转拼接后等价于从 [1, n] 中有放回选择 2m 个非降数
    // 方案数为可重组合 C(n + 2m - 1, 2m)
    cout << C(n + 2 * m - 1, 2 * m) << "\n";
    return 0;
}
