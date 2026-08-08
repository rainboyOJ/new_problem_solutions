#include <bits/stdc++.h>
using namespace std;

const long long INF = (1LL << 60);

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<long long> trip_cost(n + 1, 0);
    long long prefix = 0;
    for (int i = 1; i <= n; i++) {
        long long x;
        cin >> x;
        prefix += x;
        // round_cost[i]：来回运输一组 i 头牛的总时间
        trip_cost[i] = 2LL * m + prefix;
    }

    // dp[j]：把 j 头牛运到对岸，当前考虑若干种分组方案时的最小总时间
    vector<long long> dp(n + 1, INF);
    dp[0] = 0;

    for (int i = 1; i <= n; i++) {
        // 分组大小为 i，可以重复使用，所以是完全背包。
        for (int j = i; j <= n; j++) {
            if (dp[j - i] == INF) continue;
            dp[j] = min(dp[j], dp[j - i] + trip_cost[i]);
        }
    }

    // 最后一次不需要返回，所以减去一个单独返回的时间 m。
    cout << dp[n] - m << '\n';

    return 0;
}
