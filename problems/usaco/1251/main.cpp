/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 13:10
 * update_at: 2026-07-11 13:13
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;

int n;
long long cost[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> cost[i];
    }

    sort(cost + 1, cost + n + 1);

    long long best_money = -1;
    long long best_tuition = 0;

    for (int i = 1; i <= n; i++) {
        long long cows = n - i + 1; // 愿意支付 cost[i] 的牛数量。
        long long money = cost[i] * cows;

        // 从低学费到高学费扫描，收益相同则保留更小的学费。
        if (money > best_money) {
            best_money = money;
            best_tuition = cost[i];
        }
    }

    cout << best_money << ' ' << best_tuition << '\n';

    return 0;
}
