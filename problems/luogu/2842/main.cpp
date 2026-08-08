#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;
const int MAXW = 10005;
const int INF = 0x3f3f3f3f;

int n;                // 纸币种类数
int w;                // 要凑出的金额
int a[MAXN];          // 每种纸币的面额
int dp[MAXW];         // dp[j] = 凑出金额 j 最少需要的纸币张数

void read_input() {
    cin >> n >> w;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
}

void solve() {
    memset(dp, 0x3f, sizeof(dp));
    dp[0] = 0;

    for (int i = 1; i <= n; i++) {
        // 完全背包正序枚举，每种纸币可以无限使用。
        for (int j = a[i]; j <= w; j++) {
            dp[j] = min(dp[j], dp[j - a[i]] + 1);
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
