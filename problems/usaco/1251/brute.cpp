/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 13:10
 * update_at: 2026-07-11 13:13
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;

int n;
int cost[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    int max_cost = 0;
    for (int i = 1; i <= n; i++) {
        cin >> cost[i];
        if (max_cost < cost[i]) {
            max_cost = cost[i];
        }
    }

    long long best_money = -1;
    int best_tuition = 0;

    // 暴力枚举每一种可能学费，只适合 max_cost 很小的数据。
    for (int tuition = 1; tuition <= max_cost; tuition++) {
        int cows = 0;
        for (int i = 1; i <= n; i++) {
            if (cost[i] >= tuition) {
                cows++;
            }
        }

        long long money = 1ll * tuition * cows;
        if (money > best_money) {
            best_money = money;
            best_tuition = tuition;
        }
    }

    cout << best_money << ' ' << best_tuition << '\n';

    return 0;
}
