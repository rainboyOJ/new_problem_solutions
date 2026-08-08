#include <bits/stdc++.h>
using namespace std;

struct Bond {
    int cost_unit; // 用 1000 为单位后的投资额
    int profit;    // 这一年能拿到的利息
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long capital;
    int years, types;
    cin >> capital >> years >> types;

    vector<Bond> bonds(types);
    for (int i = 0; i < types; i++) {
        int cost, profit;
        cin >> cost >> profit;
        bonds[i] = {cost / 1000, profit};
    }

    // 资本每年最多增长 10%，所以总规模有一个很小的上界。
    // 这里直接按这个上界预处理一年内的最优收益。
    long double upper_capital = capital;
    for (int i = 0; i < years; i++) {
        upper_capital *= 1.1L;
    }
    int max_unit = static_cast<int>(upper_capital / 1000.0L) + 5;
    max_unit = max(max_unit, static_cast<int>(capital / 1000) + 5);

    vector<long long> best(max_unit + 1, 0);

    // 完全背包：在预算为 j 个“千元单位”时，最多能拿到多少利息。
    for (const auto &bond : bonds) {
        for (int j = bond.cost_unit; j <= max_unit; j++) {
            best[j] = max(best[j], best[j - bond.cost_unit] + bond.profit);
        }
    }

    for (int year = 1; year <= years; year++) {
        int unit = static_cast<int>(capital / 1000);
        if (unit > max_unit) unit = max_unit;
        capital += best[unit];
    }

    cout << capital << '\n';

    return 0;
}
