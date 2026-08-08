#include <bits/stdc++.h>
using namespace std;

const int MAXM = 1005;
const int MAXT = 10005;

int total_time;         // 总可用时间
int herb_count;         // 草药数量
int need_time[MAXM];    // 每株草药需要的时间
int herb_value[MAXM];   // 每株草药的价值
int dp[MAXT];           // dp[t] = 总时间不超过 t 时的最大总价值

void read_input() {
    cin >> total_time >> herb_count;
    for (int i = 1; i <= herb_count; i++) {
        cin >> need_time[i] >> herb_value[i];
    }
}

void solve() {
    memset(dp, 0, sizeof(dp));

    for (int i = 1; i <= herb_count; i++) {
        // 倒序枚举时间，保证每株草药最多只采一次。
        for (int t = total_time; t >= need_time[i]; t--) {
            dp[t] = max(dp[t], dp[t - need_time[i]] + herb_value[i]);
        }
    }

    cout << dp[total_time] << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    solve();

    return 0;
}
