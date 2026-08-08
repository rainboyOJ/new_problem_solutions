#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;
const int MAXW = 10005;
const int MOD = 1000000007;

int n;                // 纸币种类数
int w;                // 要凑出的金额
int a[MAXN];          // 每种纸币的面额
int dp[MAXW];         // dp[j] = 凑出金额 j 的方案数（不同顺序算不同方案）

void read_input() {
    cin >> n >> w;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
}

void solve() {
    memset(dp, 0, sizeof(dp));
    dp[0] = 1;

    // 先枚举金额再枚举纸币，这样不同顺序会被算作不同方案。
    for (int j = 1; j <= w; j++) {
        for (int i = 1; i <= n; i++) {
            if (j >= a[i]) {
                dp[j] = (dp[j] + dp[j - a[i]]) % MOD;
            }
        }
    }

    cout << dp[w] << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    solve();

    return 0;
}
