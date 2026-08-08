#include <bits/stdc++.h>
using namespace std;

const long long MOD = 100000007LL;
const int MAXN = 1000005;

long long n, m;
long long factorial[MAXN];
long long inverse_factorial[MAXN];
long long ordered_count[MAXN]; // ordered_count[i] 表示有序选择 i 个不同非空集合且异或和为 0 的方案数。

long long fast_power(long long a, long long b) {
    long long result = 1;
    while (b > 0) {
        if (b & 1) {
            result = result * a % MOD;
        }
        a = a * a % MOD;
        b >>= 1;
    }
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;

    if (m > (1LL << min(n, 20LL)) - 1 && n <= 20) {
        cout << 0 << '\n';
        return 0;
    }

    long long total_non_empty = fast_power(2, n) - 1;
    if (total_non_empty < 0) {
        total_non_empty += MOD;
    }

    factorial[0] = 1;
    for (int i = 1; i <= m; i++) {
        factorial[i] = factorial[i - 1] * i % MOD;
    }
    inverse_factorial[m] = fast_power(factorial[m], MOD - 2);
    for (int i = (int)m; i >= 1; i--) {
        inverse_factorial[i - 1] = inverse_factorial[i] * i % MOD;
    }

    ordered_count[0] = 1;
    long long perm_prefix = 1; // P(total_non_empty, i-1)，先任意选前 i-1 个不同非空集合。
    for (int i = 1; i <= m; i++) {
        // 最后一个集合由前 i-1 个集合的异或和唯一决定。
        long long bad_equal_zero = ordered_count[i - 1];
        long long bad_duplicate = 0;
        if (i >= 2) {
            long long remain_choice = (total_non_empty - (i - 2)) % MOD;
            if (remain_choice < 0) {
                remain_choice += MOD;
            }
            bad_duplicate = (long long)(i - 1) * remain_choice % MOD * ordered_count[i - 2] % MOD;
        }
        ordered_count[i] = (perm_prefix - bad_equal_zero - bad_duplicate) % MOD;
        if (ordered_count[i] < 0) {
            ordered_count[i] += MOD;
        }
        long long next_factor = (total_non_empty - (i - 1)) % MOD;
        if (next_factor < 0) {
            next_factor += MOD;
        }
        perm_prefix = perm_prefix * next_factor % MOD;
    }

    long long answer = ordered_count[m] * inverse_factorial[m] % MOD;
    cout << answer << '\n';

    return 0;
}
