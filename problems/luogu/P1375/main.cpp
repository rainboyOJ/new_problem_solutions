#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

const int MAXN = 100000 + 5;
const i64 MOD = 1000000007LL;

int n;
i64 inv[MAXN];
i64 f[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    inv[1] = 1;
    for (int i = 2; i <= n + 1; i++) {
        inv[i] = (MOD - MOD / i) * inv[MOD % i] % MOD;
    }

    f[0] = 1;

    // Catalan 递推公式：
    // C_n = C_{n-1} * (4n-2) / (n+1)
    // 在模意义下，除法改成乘逆元。
    for (int i = 1; i <= n; i++) {
        f[i] = f[i - 1] * (4LL * i - 2) % MOD;
        f[i] = f[i] * inv[i + 1] % MOD;
    }

    cout << f[n] << '\n';

    return 0;
}
