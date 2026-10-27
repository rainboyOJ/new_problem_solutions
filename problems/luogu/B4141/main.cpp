#include <bits/stdc++.h>
using namespace std;

const int MAXN = 205;

int n;
bool is_prime[MAXN];           // 埃氏筛标记
vector<int> primes;            // ≤n 的所有素数
// dp[j] 表示和为 j 的素数分解方案数（这里求的是最多项数）。
int dp[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    fill(is_prime, is_prime + n + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i * i <= n; i++) {
        if (is_prime[i]) {
            for (int j = i * i; j <= n; j += i) {
                is_prime[j] = false;
            }
        }
    }
    for (int i = 2; i <= n; i++) {
        if (is_prime[i]) primes.push_back(i);
    }

    // dp 初始化为 -1 表示不可达，dp[0] = 0 表示和为 0 用 0 项。
    fill(dp, dp + n + 1, -1);
    dp[0] = 0;
    // 0/1 背包：每个素数最多用一次，从大到小编排容量。
    for (int p : primes) {
        for (int j = n; j >= p; j--) {
            if (dp[j - p] != -1) {
                dp[j] = max(dp[j], dp[j - p] + 1);
            }
        }
    }

    cout << dp[n] << '\n';
    return 0;
}
