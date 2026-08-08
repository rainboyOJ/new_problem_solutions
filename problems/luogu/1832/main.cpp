/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-08 23:13
 * update_at: 2026-08-08 23:13
 * 筛素数 + 完全背包计数
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int maxn = 1005;
int n;
bool is_prime[maxn];
vector<int> primes;
ll dp[maxn];

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin >> n;
    fill(is_prime, is_prime + n + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i <= n; ++i)
        if (is_prime[i]) {
            primes.push_back(i);
            for (int j = i * i; j <= n; j += i)
                is_prime[j] = false;
        }
    dp[0] = 1;
    for (int p : primes)
        for (int j = p; j <= n; ++j)
            dp[j] += dp[j - p];
    cout << dp[n] << "\n";
    return 0;
}
