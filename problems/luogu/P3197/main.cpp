#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

const i64 MOD = 100003;

i64 quick_pow(i64 base, i64 exp) {
    i64 ans = 1 % MOD;
    base %= MOD;

    while (exp > 0) {
        if (exp & 1) {
            ans = ans * base % MOD;
        }
        base = base * base % MOD;
        exp >>= 1;
    }

    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    i64 m, n;
    cin >> m >> n;

    i64 total = quick_pow(m, n);
    i64 safe = m % MOD * quick_pow(m - 1, n - 1) % MOD;
    i64 ans = (total - safe) % MOD;
    if (ans < 0) {
        ans += MOD;
    }

    cout << ans << '\n';
    return 0;
}
