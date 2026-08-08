#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, capacity;
    cin >> n >> capacity;

    vector<int> dp(capacity + 1, 0);
    vector<int> prev_dp(capacity + 1, 0);

    for (int i = 1; i <= n; ++i) {
        int value, weight, count;
        cin >> value >> weight >> count;

        prev_dp = dp;
        for (int j = 0; j <= capacity; ++j) {
            for (int k = 1; k <= count && k * weight <= j; ++k) {
                // 直接枚举当前物品选几件，是最朴素的多重背包写法。
                dp[j] = max(dp[j], prev_dp[j - k * weight] + k * value);
            }
        }
    }

    cout << dp[capacity] << '\n';
    return 0;
}
