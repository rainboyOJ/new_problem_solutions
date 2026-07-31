/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-07-31 23:48
 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, target;
    cin >> n >> m >> target;
    vector<int> basic_cost(n), piece_cost(n);
    vector<vector<int> > goods(n);
    for (int i = 0; i < n; i++) cin >> basic_cost[i] >> piece_cost[i];
    for (int i = 0; i < m; i++) {
        int value, warehouse;
        cin >> value >> warehouse;
        goods[warehouse].push_back(value);
    }

    int maximum_cost = 0;
    for (int i = 0; i < n; i++) {
        if (goods[i].empty()) continue;
        sort(goods[i].begin(), goods[i].end(), greater<int>());
        maximum_cost += basic_cost[i] + piece_cost[i] * (int)goods[i].size();
    }

    const int NEGATIVE_INFINITY = -1000000000;
    vector<int> dp(maximum_cost + 1, NEGATIVE_INFINITY);
    dp[0] = 0;
    for (int warehouse = 0; warehouse < n; warehouse++) {
        if (goods[warehouse].empty()) continue;
        vector<int> next_dp = dp;
        int profit = -basic_cost[warehouse];
        for (int count = 1; count <= (int)goods[warehouse].size(); count++) {
            profit += goods[warehouse][count - 1] - piece_cost[warehouse];
            int cost = basic_cost[warehouse] + count * piece_cost[warehouse];
            for (int old_cost = 0; old_cost + cost <= maximum_cost; old_cost++) {
                if (dp[old_cost] == NEGATIVE_INFINITY) continue;
                next_dp[old_cost + cost] = max(next_dp[old_cost + cost], dp[old_cost] + profit);
            }
        }
        dp.swap(next_dp);
    }

    int answer = maximum_cost;
    for (int cost = 0; cost <= maximum_cost; cost++) {
        if (dp[cost] >= target) answer = min(answer, cost);
    }
    cout << answer << '\n';
    return 0;
}
