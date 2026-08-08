#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;
const int INF = 1000000000;

int n, q_cnt;
int h[MAXN];
int dp[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // brute.cpp：朴素 DP。
    // 对每个终点 i，枚举所有能直接飞到它的起点 j。
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> h[i];
    }

    cin >> q_cnt;
    while (q_cnt--) {
        int k;
        cin >> k;

        for (int i = 1; i <= n; i++) {
            dp[i] = INF;
        }
        dp[1] = 0;

        for (int i = 2; i <= n; i++) {
            int left = max(1, i - k);
            for (int j = left; j <= i - 1; j++) {
                int cost = dp[j];
                if (h[j] <= h[i]) {
                    cost++;
                }
                dp[i] = min(dp[i], cost);
            }
        }

        cout << dp[n] << '\n';
    }

    return 0;
}
