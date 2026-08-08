#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;
const int MAXW = 10005;
const int MOD = 1000000007;

int n;                // 纸币种类数
int w;                // 要凑出的金额
int a[MAXN];          // 每种纸币的面额
int dp[MAXW];         // dp[j] = 凑出金额 j 的组合数（组合，不同顺序算同一种）

void read_input() {
    cin >> n >> w;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
}

void solve() {
    memset(dp, 0, sizeof(dp));
    dp[0] = 1;

    // 先枚举纸币再枚举金额，这样不同顺序会被合并为同一种组合。
    for (int i = 1; i <= n; i++) {
        for (int j = a[i]; j <= w; j++) {
            dp[j] = (dp[j] + dp[j - a[i]]) % MOD;
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
