#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;
const int MAXM = 1005;
const int MAXX = 1005;

int n;
int limit_detect;          // 敌人的探查能力上限
int limit_money;           // 手头的钱数上限
int info_value[MAXN];      // 第 i 个间谍能拿到的资料量
int detect_cost[MAXN];     // 第 i 个间谍带来的探查风险
int money_cost[MAXN];      // 第 i 个间谍需要的工资
int dp[MAXM][MAXX];        // dp[j][k] = 风险不超过 j、金钱不超过 k 时最多能拿到多少资料

void read_input() {
    cin >> n >> limit_detect >> limit_money;
    for (int i = 1; i <= n; i++) {
        cin >> info_value[i] >> detect_cost[i] >> money_cost[i];
    }
}

void solve() {
    memset(dp, 0, sizeof(dp));

    for (int i = 1; i <= n; i++) {
        // 两维容量都倒序，保证每个间谍最多只选一次。
        for (int j = limit_detect; j >= detect_cost[i]; j--) {
            for (int k = limit_money; k >= money_cost[i]; k--) {
                dp[j][k] = max(dp[j][k],
                               dp[j - detect_cost[i]][k - money_cost[i]] + info_value[i]);
            }
        }
    }

    cout << dp[limit_detect][limit_money] << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    solve();

    return 0;
}
