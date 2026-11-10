/**
 * Problem: luogu P5023 - [NOIP 2018 提高组] 填数游戏
 * Author: rainboy
 * Date: 2026-11-11 00:50
 * Description: 对称性分析 + 基础表与公比 3 快速幂递推
 */
#include <iostream>
#include <algorithm>

using namespace std;

using ll = long long;

const int MOD = 1e9 + 7;

ll qpow(ll a, ll b) {
    ll res = 1;
    a %= MOD;
    while (b > 0) {
        if (b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

const int F[9][9] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 2, 4, 8, 16, 32, 64, 128, 256},
    {0, 4, 12, 36, 108, 324, 972, 2916, 8748},
    {0, 8, 36, 112, 336, 1008, 3024, 9072, 27216},
    {0, 16, 108, 336, 912, 2688, 8064, 24192, 72576},
    {0, 32, 324, 1008, 2688, 7136, 21312, 63936, 191808},
    {0, 64, 972, 3024, 8064, 21312, 56768, 170112, 510336},
    {0, 128, 2916, 9072, 24192, 63936, 170112, 453504, 1360128},
    {0, 256, 8748, 27216, 72576, 191808, 510336, 1360128, 3626752}
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    // 对称性：钦定 n <= m
    if (n > m) swap(n, m);

    if (n == 1) {
        cout << qpow(2, m) << "\n";
        return 0;
    }

    if (m <= 8) {
        cout << F[n][m] << "\n";
        return 0;
    }

    // 当 m > 8 时，由于 m > n，使用 F[n][n+1] * 3^(m - n - 1)
    ll base_val;
    if (n != 8) {
        base_val = F[n][n + 1];
    } else {
        base_val = 10879488LL;
    }

    ll ans = base_val % MOD * qpow(3, m - n - 1) % MOD;
    cout << ans << "\n";

    return 0;
}
