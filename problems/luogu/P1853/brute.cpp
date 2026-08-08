#include <bits/stdc++.h>
using namespace std;

struct Bond {
    int cost_unit;
    int profit;
};

int years, types;
long long start_capital;
vector<Bond> bonds;

// 暴力枚举某一年所有可行的投资组合，找这一年的最大利息。
long long brute_one_year(int idx, long long remain_unit, long long current_profit) {
    if (idx == types) {
        return current_profit;
    }

    long long best = current_profit;
    for (long long cnt = 0; cnt * bonds[idx].cost_unit <= remain_unit; cnt++) {
        best = max(best, brute_one_year(idx + 1,
                                        remain_unit - cnt * bonds[idx].cost_unit,
                                        current_profit + cnt * bonds[idx].profit));
    }
    return best;
}

long long dfs_year(int year, long long capital) {
    if (year == years) {
        return capital;
    }

    long long unit = capital / 1000;
    long long best_profit = brute_one_year(0, unit, 0);
    return dfs_year(year + 1, capital + best_profit);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> start_capital >> years >> types;
    bonds.resize(types);
    for (int i = 0; i < types; i++) {
        int cost, profit;
        cin >> cost >> profit;
        bonds[i] = {cost / 1000, profit};
    }

    cout << dfs_year(0, start_capital) << '\n';

    return 0;
}
