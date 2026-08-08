#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T, N, money;
    cin >> T >> N >> money;

    vector<vector<int>> price(T, vector<int>(N));
    for (int i = 0; i < T; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> price[i][j];
        }
    }

    // 逐天处理相邻两天之间的收益，把金币滚动更新。
    for (int day = 0; day + 1 < T; ++day) {
        vector<int> dp(money + 1, 0);

        for (int item = 0; item < N; ++item) {
            int cost = price[day][item];
            int gain = price[day + 1][item] - price[day][item];
            if (gain <= 0 || cost > money) {
                continue;
            }

            // 完全背包：同一种纪念品可以买很多件。
            for (int cap = cost; cap <= money; ++cap) {
                dp[cap] = max(dp[cap], dp[cap - cost] + gain);
            }
        }

        money += dp[money];
    }

    cout << money << '\n';
    return 0;
}
