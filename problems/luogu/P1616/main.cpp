#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10005;

int t, m;
int cost[MAXN];
int value[MAXN];
vector<long long> dp; // dp[j] 表示时间不超过 j 时的最大奖励

void read_input() {
    cin >> t >> m;
    for (int i = 1; i <= m; i++) {
        cin >> cost[i] >> value[i];
    }
}

void solve() {
    dp.assign(t + 1, 0);

    for (int i = 1; i <= m; i++) {
        // 完全背包可以重复选同一种草药，所以容量必须正序枚举。
        for (int j = cost[i]; j <= t; j++) {
            dp[j] = max(dp[j], dp[j - cost[i]] + value[i]);
        }
    }

    cout << dp[t] << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    solve();

    return 0;
}
