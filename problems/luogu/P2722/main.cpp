#include <bits/stdc++.h>
using namespace std;

const int MAXT = 10005;
const int MAXN = 10005;

int t, n;
int points[MAXN];
int cost[MAXN];
int dp[MAXT]; // dp[j] 表示时间不超过 j 时能获得的最大全分

void read_input() {
    cin >> t >> n;
    for (int i = 1; i <= n; i++) {
        cin >> points[i] >> cost[i];
    }
}

void solve() {
    for (int i = 1; i <= n; i++) {
        // 每种题目可以选很多道，所以容量必须正序枚举。
        for (int j = cost[i]; j <= t; j++) {
            dp[j] = max(dp[j], dp[j - cost[i]] + points[i]);
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
