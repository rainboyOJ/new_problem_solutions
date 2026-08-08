// brute.cpp：状压 DP 直接模拟购买顺序。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 12;
const int INF = 1e9;

int direct_cost, gift_cnt;
int discount[MAXN][MAXN];
int dp[1 << MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> direct_cost >> gift_cnt;
    for (int i = 0; i < gift_cnt; i++) {
        for (int j = 0; j < gift_cnt; j++) {
            cin >> discount[i][j];
        }
    }

    int max_mask = 1 << gift_cnt;
    for (int i = 0; i < max_mask; i++) {
        dp[i] = INF;
    }
    dp[0] = 0;

    for (int mask = 0; mask < max_mask; mask++) {
        if (dp[mask] == INF) {
            continue;
        }

        for (int j = 0; j < gift_cnt; j++) {
            if ((mask >> j) & 1) {
                continue;
            }

            int cost = direct_cost;
            for (int i = 0; i < gift_cnt; i++) {
                if (((mask >> i) & 1) == 0) {
                    continue;
                }
                cost = min(cost, discount[i][j]);
            }

            int next_mask = mask | (1 << j);
            dp[next_mask] = min(dp[next_mask], dp[mask] + cost);
        }
    }

    cout << dp[max_mask - 1] << '\n';

    return 0;
}
