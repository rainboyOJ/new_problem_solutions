#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

const i64 MOD = 998244353;

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

    i64 n, k;
    cin >> n >> k;

    i64 ways_for_one_metal = quick_pow(2, k) - 1;
    if (ways_for_one_metal < 0) {
        ways_for_one_metal += MOD;
    }

    cout << quick_pow(ways_for_one_metal, n) << '\n';
    return 0;
}
