#include <bits/stdc++.h>
using namespace std;

const int INF = 1000000000;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, h;
    cin >> n >> h;

    vector<int> dp(h + 1, INF);
    dp[0] = 0;

    for (int i = 1; i <= n; ++i) {
        int weight, cost;
        cin >> weight >> cost;
        for (int j = 0; j <= h; ++j) {
            if (dp[j] == INF) {
                continue;
            }
            int next_weight = min(h, j + weight);
            dp[next_weight] = min(dp[next_weight], dp[j] + cost);
        }
    }

    cout << dp[h] << '\n';
    return 0;
}
