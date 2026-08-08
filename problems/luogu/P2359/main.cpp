#include <bits/stdc++.h>
using namespace std;

const int MAXS = 100;
const int MOD = 1000000009;

int n;
bool is_prime[1000];
int dp[MAXS], ndp[MAXS]; // dp[ab]：当前长度下，最后两位是 ab 的方案数

bool check_prime(int x) {
    if (x < 2) {
        return false;
    }
    for (int i = 2; i * i <= x; i++) {
        if (x % i == 0) {
            return false;
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    for (int i = 100; i <= 999; i++) {
        is_prime[i] = check_prime(i);
    }

    if (n < 3) {
        cout << 0 << '\n';
        return 0;
    }

    // 长度为 3 时，所有三位素数都可以作为起点。
    for (int x = 100; x <= 999; x++) {
        if (!is_prime[x]) {
            continue;
        }
        int last2 = x % 100;
        dp[last2]++;
    }

    for (int len = 4; len <= n; len++) {
        for (int i = 0; i <= 99; i++) {
            ndp[i] = 0;
        }
        for (int ab = 0; ab <= 99; ab++) {
            if (dp[ab] == 0) {
                continue;
            }
            for (int d = 0; d <= 9; d++) {
                int num = ab * 10 + d;
                if (!is_prime[num]) {
                    continue;
                }
                int next_last2 = num % 100;
                ndp[next_last2] = (ndp[next_last2] + dp[ab]) % MOD;
            }
        }
        for (int i = 0; i <= 99; i++) {
            dp[i] = ndp[i];
        }
    }

    int ans = 0;
    for (int ab = 0; ab <= 99; ab++) {
        ans += dp[ab];
        if (ans >= MOD) {
            ans -= MOD;
        }
    }

    cout << ans << '\n';
    return 0;
}
