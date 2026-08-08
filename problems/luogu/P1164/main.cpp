#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;
const int MAXM = 10005;

int n;              // 菜品种类数
int money;          // 需要恰好花掉的钱
int a[MAXN];        // 每种菜的价格
int dp[MAXM];       // dp[j] = 恰好花掉 j 元的方案数

void read_input() {
    cin >> n >> money;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
}

void solve() {
    memset(dp, 0, sizeof(dp));
    dp[0] = 1;

    for (int i = 1; i <= n; i++) {
        // 倒序枚举金额，保证每种菜最多只选一次。
        for (int j = money; j >= a[i]; j--) {
            dp[j] += dp[j - a[i]];
        }
    }

    cout << dp[money] << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    solve();

    return 0;
}
